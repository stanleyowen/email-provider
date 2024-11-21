// Include the necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "Auth/auth.h"
#include "Auth/session.h"
#include "Base/layout.h"

// Callback function to write the response data
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *file = (FILE *)userdata;
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, file);
    return total_size;
}

int main(void)
{
    // Declare the necessary variables
    char emailAddress[254], emailPassword[128], accountType[5], mailServer[255], mailServerURL[500], emailID[10];

    // Declare a variable to continue the session
    _Bool continueSession;

    // Print the layout of the email client
    layout(&continueSession);

    // Loop to continue the session until the user decides to exit
    do
    {
        const char *sessionFileName = "session.txt";
        const char *outputFileName = "output.html";

        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();

        if (curl)
        {
            // Check if the session file exists
            FILE *session_file = fopen(sessionFileName, "r");

            if (session_file)
            {
                // Read the user session from the file
                read_user_session(sessionFileName, emailAddress, emailPassword, accountType, mailServer);
                fclose(session_file);
            }
            else
            {
                // If the session file does not exist, authenticate the user input
                authenticate_user_input(emailAddress, emailPassword, accountType, mailServer);

                // Combine the account type and mail server to form the mail server URL
                combine_url(mailServerURL, accountType, mailServer, NULL);

                // Save the user session to a file to maintain the user's credentials in the next session
                save_user_session(sessionFileName, emailAddress, emailPassword, accountType, mailServer);
            }

            // Prompt the user to enter the email ID
            printf("Enter the email ID: ");
            scanf("%9s", &emailID);

            combine_url(mailServerURL, accountType, mailServer, emailID);

            // Open the output file to write the email content
            FILE *output_file = fopen(outputFileName, "w");
            if (!output_file)
            {
                perror("Failed to open output file");
                curl_easy_cleanup(curl);
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
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

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
                printf("Email retrieved successfully!");
                // printf("Email retrieved successfully! Content saved to %s\n", outputFileName);
            }

            // Cleanup the CURL object
            curl_easy_cleanup(curl);
            fclose(output_file);

// Open the output file to display the email content with the default browser
#ifdef _WIN32
            system("start output.html");
#elif __linux__
            system("xdg-open output.html");
#elif __APPLE__
            system("open output.html");
#endif

        }
        else
        {
            fprintf(stderr, "Failed to initialize CURL.\n");
        }
    } while (continueSession != 0);

    return 0;
}