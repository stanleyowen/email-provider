#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

#include "auth.h"

void composeEmail(char *destinationEmail, char *emailSubject, char *emailContent)
{
    // _Bool advance = 0;
    // Initialize emailContent as an empty string
    emailContent[0] = '\0';

    // Prompt the user to enter the destination email
    printf("Destination: ");
    scanf("%254s", destinationEmail);

    getchar(); // Consume the newline character left by scanf to avoid issues with fgets

    // Prompt the user to enter the email subject
    printf("Subject: ");
    // Use fgets to read the subject line
    fgets(emailSubject, 100, stdin);
    // Remove the newline character if present
    size_t len = strlen(emailSubject);
    if (len > 0 && emailSubject[len - 1] == '\n')
    {
        emailSubject[len - 1] = '\0';
    }

    // Prompt the user to enter the email content
    printf("Contents (end with two consecutive Enter key presses):\n");

    char line[1000];
    int emptyLineCount = 0;
    while (1)
    {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "\n") == 0)
        {
            emptyLineCount++;
            if (emptyLineCount == 2)
            {
                break;
            }
        }
        else
        {
            emptyLineCount = 0;
        }
        strcat(emailContent, line);
    }

    // Could add the feature such as cc, bcc, attachments, etc in the future
}