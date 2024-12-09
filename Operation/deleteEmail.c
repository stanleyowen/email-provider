#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "auth.h"
#include "readEmail.h"
#include "deleteEmail.h"

void deleteEmailByID(const char *mailServerURL, char *emailAddress, char *emailPassword)
{
    // Preview the inbox before deleting an email
    readInbox(mailServerURL, emailAddress, emailPassword);

    CURL *curl = curl_easy_init();
    char emailID[10];

    // Prompt the user to enter the email ID
    printf("Enter the email ID to delete: ");
    scanf("%9s", emailID);

    // Construct the URL to select the mailbox
    char selectMailboxURL[256];
    snprintf(selectMailboxURL, sizeof(selectMailboxURL), "%sINBOX", mailServerURL);

    // Disable SSL verification to avoid certificate-related issues
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    // Set CURL options for selecting the mailbox
    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, selectMailboxURL);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT INBOX");

    // Perform the SELECT request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        // Mark the email as deleted
        char storeCommand[256];
        snprintf(storeCommand, sizeof(storeCommand), "STORE %s +FLAGS \\Deleted", emailID);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, storeCommand);

        // Perform the STORE request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            // Expunge the deleted email
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXPUNGE");
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            else
            {
                printf("Email with ID %s deleted successfully.\n", emailID);
            }
        }
    }

    curl_easy_cleanup(curl);
}