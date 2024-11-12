// Include the necessary headers
#include <stdio.h>
#include <curl/curl.h>
#include "Auth/auth.h"

int main(void)
{
    // Declare the necessary variables
    char emailAddress[254], emailPassword[128], accountType[5], mailServer[255], mailServerURL[303];

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl)
    {
        // Check if the session file exists
        if (fopen("session.txt", "r"))
        {
            // Read the user session from the file
            read_user_session(emailAddress, emailPassword, accountType, mailServerURL);
        }
        else
        {
            // If the session file does not exist, authenticate the user input
            authenticate_user_input(emailAddress, emailPassword, accountType, mailServer);

            // Combine the account type and mail server to form the mail server URL
            combine_url(mailServerURL, accountType, mailServer);

            // Save the user session to a file to maintain the user's credentials in the next session
            save_user_session(emailAddress, emailPassword, accountType, mailServerURL);
        }

        /*
         * Initialize the CURL object with the necessary options:
         * CURLOPT_USERNAME: The username or email to use for authentication
         * CURLOPT_PASSWORD: The password to use for authentication
         * CURLOPT_URL: The URL of the website to authenticate against
         */
        curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
        curl_easy_setopt(curl, CURLOPT_URL, mailServerURL);

        // Enable verbose mode to display the authentication process
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);

        // Check if the authentication was successful
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else
        {
            printf("Login successful!\n");
        }

        // Cleanup the CURL object
        curl_easy_cleanup(curl);
    }
    else
    {
        fprintf(stderr, "Failed to initialize CURL.\n");
    }

    return 0;
}