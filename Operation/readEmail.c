#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "auth.h"
#include "readEmail.h"

#define MAX_UID_LENGTH 32
#define MAX_SUBJECTS 10000
#define MAX_SUBJECT_LENGTH 256

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
    previewUIDInbox(mailServerURL, emailAddress, emailPassword);

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
        return;
    }
    else
    {
        printf("Email retrieved successfully!\n");
    }

    fclose(output_file);
    curl_easy_cleanup(curl);

    // Execute the Python script
    int result = system("python3 ./Script/parseHTML.py");
    if (result != 0)
    {
        fprintf(stderr, "Failed to execute the Python script.\n");
        return;
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

typedef struct
{
    char uid[MAX_UID_LENGTH];
    char subject[MAX_SUBJECT_LENGTH];
} EmailInfo;

typedef struct
{
    EmailInfo emails[MAX_SUBJECTS];
    int count;
} EmailInfoList;

size_t write_callback_uid_inbox(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    EmailInfoList *email_info_list = (EmailInfoList *)userdata;
    size_t total_size = size * nmemb;

    // Process the received data to extract email subjects and UIDs
    char *line = strtok((char *)ptr, "\r\n");
    while (line != NULL)
    {
        if (strstr(line, "UID ") != NULL)
        {
            // Extract the UID
            char *uid_start = strstr(line, "UID ") + 4;
            char *uid_end = strchr(uid_start, ' ');
            if (uid_end != NULL)
            {
                size_t uid_length = uid_end - uid_start;
                strncpy(email_info_list->emails[email_info_list->count].uid, uid_start, uid_length);
                email_info_list->emails[email_info_list->count].uid[uid_length] = '\0'; // Ensure null-termination
            }
        }
        else if (strstr(line, "Subject:") != NULL)
        {
            // Append the email subject to the list
            strncpy(email_info_list->emails[email_info_list->count].subject, line + 9, MAX_SUBJECT_LENGTH - 1);
            email_info_list->emails[email_info_list->count].subject[MAX_SUBJECT_LENGTH - 1] = '\0'; // Ensure null-termination
            email_info_list->count++;
        }
        line = strtok(NULL, "\r\n");
    }

    return total_size;
}

void previewUIDInbox(char *mailServerURL, char *emailAddress, char *emailPassword)
{
    CURL *curl = curl_easy_init();
    EmailInfoList email_info_list = {.count = 0}; // Initialize the email info list

    // Modify the URL to point to the inbox
    char url[256];
    snprintf(url, sizeof(url), "%sINBOX", mailServerURL);

    // Disable SSL verification to avoid certificate-related issues
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH 1:* (UID BODY[HEADER.FIELDS (SUBJECT)])");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_uid_inbox);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &email_info_list);

    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        // Display the UIDs and subjects to the user
        for (int i = 0; i < email_info_list.count; i++)
        {
            printf("UID: %s, Subject: %s\n", email_info_list.emails[i].uid, email_info_list.emails[i].subject);
        }
    }

    curl_easy_cleanup(curl);
}

// Structure to hold the email subjects and count
// Declare a 2D array to store the email subjects
typedef struct
{
    char subjects[MAX_SUBJECTS][MAX_SUBJECT_LENGTH];
    int count;
} SubjectList;

size_t write_callback_inbox(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    SubjectList *subject_list = (SubjectList *)userdata;
    size_t total_size = size * nmemb;

    // Process the received data to extract email subjects
    char *line = strtok((char *)ptr, "\r\n");
    while (line != NULL)
    {
        if (strncmp(line, "Subject:", 8) == 0)
        {
            // Append the email subject to the list
            strncpy(subject_list->subjects[subject_list->count], line + 9, MAX_SUBJECT_LENGTH - 1);
            subject_list->subjects[subject_list->count][MAX_SUBJECT_LENGTH - 1] = '\0'; // Ensure null-termination
            subject_list->count++;
        }
        line = strtok(NULL, "\r\n");
    }

    return total_size;
}

void readInbox(char *mailServerURL, char *emailAddress, char *emailPassword)
{
    CURL *curl = curl_easy_init();
    SubjectList subject_list = {.count = 0}; // Initialize the subject list

    // Modify the URL to point to the inbox
    char url[256];
    snprintf(url, sizeof(url), "%sINBOX", mailServerURL);

    // Disable SSL verification to avoid certificate-related issues
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "FETCH 1:* (BODY[HEADER.FIELDS (SUBJECT)])");
    // curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "STATUS INBOX (MESSAGES)");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_inbox);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &subject_list);

    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        printf("Number of emails in inbox: %d\n", subject_list.count);
        for (int i = 0; i < subject_list.count; i++)
        {
            printf("%d. %s\n", i + 1, subject_list.subjects[i]);
        }
    }

    curl_easy_cleanup(curl);
}