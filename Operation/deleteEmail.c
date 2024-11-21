#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "auth.h"
#include "deleteEmail.h"

void deleteEmailByID(CURL *curl, const char *mailServerURL)
{
    char emailID[10];

    // Prompt the user to enter the email ID
    printf("Enter the email ID to delete: ");
    scanf("%9s", emailID);

    // Construct the URL to delete the email
    char url[256];
    snprintf(url, sizeof(url), "%s%s", mailServerURL, emailID);
    printf("Mail Server URL: %s\n", url);

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELE");
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Email with ID %s deleted successfully.\n", emailID);
    }
}