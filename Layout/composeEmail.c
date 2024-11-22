#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <time.h>

#include "auth.h"

void getCurrentDate(char *dateStr, size_t maxSize)
{
    time_t now = time(NULL);
    struct tm *t = gmtime(&now);
    strftime(dateStr, maxSize, "%a, %d %b %Y %H:%M:%S +0000", t);
}

void composeEmail(char *timestamp, char *destinationEmail, char *emailSubject, char *emailContent)
{
    // _Bool advance = 0;

    // Set the timestamp
    getCurrentDate(timestamp, 100);

    // Prompt the user to enter the destination email
    printf("Destination: ");
    scanf("%254s", destinationEmail);

    // Prompt the user to enter the email subject
    printf("Subject: ");
    scanf("%99s", emailSubject);

    // Prompt the user to enter the email content
    printf("Contents: ");
    scanf("%999s", emailContent);

    // Could add the feature such as cc, bcc, attachments, etc in the future
}