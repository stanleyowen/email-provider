// Include the necessary headers
#include <stdio.h>

#include "layout.h"

// Print the layout of the email client
void layout(_Bool *continueSession)
{
    int userChoice;

    printf("Email Client\n");
    printf("1. View Inbox\n");
    printf("2. View Email\n");
    printf("3. Delete Email\n");
    printf("4. Compose Email\n");
    printf("5. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &userChoice);

    if (userChoice == 1)
    {
        printf("Viewing Inbox...\n");
    }
    else if (userChoice == 2)
    {
        printf("Viewing Email...\n");
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
    }
    else
    {
    }

    printf("\n");
}