// Include the necessary headers
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#include "auth.h"
#include "session.h"

/*
 * emailAddress: The email address to use for authentication (https://www.rfc-editor.org/errata/eid1690)
 * emailPassword: The password to use for authentication (https://stackoverflow.com/questions/98768/should-i-impose-a-maximum-length-on-passwords)
 * mailServer: The mail server to use for authentication (https://en.wikipedia.org/wiki/Fully_qualified_domain_name)
 * url: The combined account type and mail server to use for authentication
 */
void authenticate_user_input(char *emailAddress, char *emailPassword, char *mailServer)
{
    printf("Email Address\t\t\t: ");
    scanf("%254s", emailAddress);

    printf("Password\t\t\t: ");
    scanf("%128s", emailPassword);

    printf("Mail Server\t\t\t: ");
    scanf("%255s", mailServer);
}

/*
 * url: The combined account type and mail server to use for authentication in the format accountType://mailServer
 * Example: pop3://mail.ntust.edu.tw
 */
void combine_url(char *mailServerURL, char *accountType, char *mailServer, char *emailID)
{
    if (emailID == NULL)
        sprintf(mailServerURL, "%s://%s/", accountType, mailServer);
    else if (accountType && mailServer && emailID)
    {
        // Check if the account type is SMTP
        if (strcmp(accountType, "pop3") == 0)
            sprintf(mailServerURL, "%s://%s/%s", accountType, mailServer, emailID);
        else
            sprintf(mailServerURL, "%s://%s/INBOX/;UID=%s", accountType, mailServer, emailID);
    }
    else
    {
        sprintf(mailServerURL, "%s/%s", mailServerURL, emailID);
    }
}

int login(CURL *curl, const char *sessionFileName, char *mailServerURL, char *emailAddress, char *emailPassword, char *null)
{

    // Declare necessary local variables and return it to the main function using pointers
    char accountType[5] = "pop3s", mailServer[255];

    FILE *session_file = fopen(sessionFileName, "r");

    if (session_file)
    {
        // Read the user session from the file
        read_user_session(sessionFileName, emailAddress, emailPassword, mailServer);
        fclose(session_file);
    }
    else
    {
        // If the session file does not exist, authenticate the user input
        authenticate_user_input(emailAddress, emailPassword, mailServer);

        // Combine the account type and mail server to form the mail server URL
        combine_url(mailServerURL, accountType, mailServer, NULL);

        // Save the user session to a file to maintain the user's credentials in the next session
        save_user_session(sessionFileName, emailAddress, emailPassword, mailServer);
    }

    // Combine the account type and mail server to form the mail server URL
    combine_url(mailServerURL, accountType, mailServer, NULL);

    // Initialize the CURL object with the necessary options
    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, mailServerURL);

    // Set the sender's email address for sending emails
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, emailAddress);

    // Perform the login operation
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK)
    {
        fprintf(stderr, "Failed to login: %s\n", curl_easy_strerror(res));
        return 0;
    }
    else
    {
        printf("Login successful.\n");
        return 1;
    }
}