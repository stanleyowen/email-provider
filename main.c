// Include the necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "Auth/auth.h"
#include "Auth/session.h"
#include "Base/layout.h"

// // Callback function to write the response data
// static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
// {
//     FILE *file = (FILE *)userdata;
//     size_t total_size = size * nmemb;
//     fwrite(ptr, size, nmemb, file);
//     return total_size;
// }

int main(void)
{
    // Declare the necessary variables
    char emailAddress[254], emailPassword[128], mailServerURL[500], emailID[10];

    // Declare a variable to continue the session
    _Bool continueSession;

    const char *sessionFileName = "session.txt";
    const char *outputFileName = "output.html";

    CURL *curl;
    curl = curl_easy_init();

    // Loop to continue the session until the user decides to exit
    do
    {
        if (curl)
        {
            login(curl, sessionFileName, emailAddress, emailPassword, mailServerURL);

            // Print the layout of the email client
            layout(&continueSession);
        }
        else
        {
            fprintf(stderr, "Failed to initialize CURL.\n");
        }

    } while (continueSession != 0);

    return 0;
}