#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void readEmailByID(const char *outputFileName, char *mailServerURL, char *emailAddress, char *emailPassword)
{
    CURL *curl = curl_easy_init();
    char emailID[10];

    // Prompt the user to enter the email ID
    printf("Enter the email ID: ");
    scanf("%9s", emailID);

    // Modify the URL to point to the inbox
    char url[256];
    snprintf(url, sizeof(url), "%sINBOX/;UID=%s", mailServerURL, emailID);

    // Open the output file to write the email content
    FILE *output_file = fopen(outputFileName, "wb");
    if (!output_file)
    {
        perror("Failed to open output file");
        curl_easy_cleanup(curl);
        return;
    }

    printf("Mail Server URL: %s\n", url);

    // Disable SSL verification to avoid certificate-related issues
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the callback function to write the response data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

    // Perform the fetch
    CURLcode res = curl_easy_perform(curl);

    // Check if the fetch was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Email retrieved successfully!\n");
    }

    fclose(output_file);
    curl_easy_cleanup(curl);

    // Execute the Python script
    int result = system("python3 ./operation/parseHTML.py");
    if (result != 0)
    {
        fprintf(stderr, "Failed to execute the Python script.\n");
    }

    // Open the output file to display the email content with the default browser
#ifdef _WIN32
    system("start output.html");
#elif __linux__
    system("xdg-open output.html");
#elif __APPLE__
    system("open output.html");
#endif
}

size_t write_callback_inbox(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    // Append the received data to the buffer
    strncat((char *)userdata, (char *)ptr, size * nmemb);
    return size * nmemb;
}

void readInbox(char *mailServerURL, char *emailAddress, char *emailPassword)
{
    CURL *curl = curl_easy_init();
    char response[1024] = {0}; // Buffer to store the response

    // Modify the URL from pop3s to imaps
    char url[256];
    strncpy(url, mailServerURL, sizeof(url) - 1);
    url[sizeof(url) - 1] = '\0'; // Ensure null-termination

    // Replace the first five characters of the mailServerURL from "pop3s" to "imaps"
    strncpy(url, "imaps", 5);

    // Disable SSL verification to avoid certificate-related issues
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "STATUS INBOX (MESSAGES)");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_inbox);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        // Parse the response to extract the number of messages
        char *messages_str = strstr(response, "MESSAGES");
        if (messages_str)
        {
            int num_messages;
            sscanf(messages_str, "MESSAGES %d", &num_messages);
            printf("Number of emails in inbox: %d\n", num_messages);
        }
        else
        {
            printf("Failed to retrieve the number of messages.\n");
        }
    }

    curl_easy_cleanup(curl);
}