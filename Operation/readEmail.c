#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "auth.h"
#include "readEmail.h"

// Callback function to write the response data
static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    FILE *file = (FILE *)userdata;
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, file);
    return total_size;
}

// size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
// {
//     size_t total_size = size * nmemb;
//     fwrite(ptr, size, nmemb, stdout); // Write directly to stdout
//     return total_size;
// }

void readEmailByID(CURL *curl, const char *outputFileName, char *mailServerURL)
{
    char emailID[10];

    // Prompt the user to enter the email ID
    printf("Enter the email ID: ");
    scanf("%9s", &emailID);

    // Construct the URL to fetch the email
    char url[256];
    snprintf(url, sizeof(url), "%s%s", mailServerURL, emailID);

    // Open the output file to write the email content
    FILE *output_file = fopen(outputFileName, "wb");
    if (!output_file)
    {
        perror("Failed to open output file");
        curl_easy_cleanup(curl);
    }

    printf("Mail Server URL: %s\n", url);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

    // Enable verbose mode to display the authentication process
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Email retrieved successfully!\n");
    }

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

void readInbox(CURL *curl, char *mailServerURL)
{
    // combine_url(mailServerURL, "pop3s", "pop.gmail.com/INBOX", NULL);
    printf("Mail Server URL: %s\n", mailServerURL);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "LIST");
    curl_easy_setopt(curl, CURLOPT_URL, mailServerURL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    // Enable verbose mode to display the authentication process
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Email retrieved successfully!\n");
    }
}