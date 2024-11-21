// Include the necessary headers
#include <stdio.h>
#include <curl/curl.h>

#include "layout.h"
#include "../Operation/readEmail.h"

// Print the layout of the email client
void layout(CURL *curl, _Bool *continueSession, const char *outputFileName, char *mailServerURL)
{
    int userChoice;

    printf("Email Client\n");
    printf("1. View Inbox\n");
    printf("2. View Email\n");
    printf("3. Delete Email\n");
    printf("4. Compose Email\n");
    printf("5. Exit\n");

    // Loop the prompt until the user decides to exit the application
    do
    {
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        if (userChoice == 1)
        {
            readInbox(curl, mailServerURL);
        }
        else if (userChoice == 2)
        {
            readEmailByID(curl, outputFileName, mailServerURL);
        }
        else if (userChoice == 3)
        {
            printf("Deleting Email...\n");
        }
        else if (userChoice == 4)
        {
            printf("Composing Email...\n");
        }
        else if (userChoice == 5)
        {
            printf("Exiting application\n");
            *continueSession = 0;
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    } while (continueSession != 0);

    printf("\n");
}