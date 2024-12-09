// Include the necessary headers
#include <stdio.h>
#include <curl/curl.h>

#include "base.h"
#include "composeEmail.h"
#include "../Auth/session.h"
#include "../Operation/readEmail.h"
#include "../Operation/deleteEmail.h"
#include "../Operation/sendEmail.h"
#include "../Operation/drafts.h" // 引入 drafts.h

// Print the layout of the email client
void base(_Bool *continueSession, const char *outputFileName, const char *sessionFileName, char *mailServerURL, char *emailAddress, char *emailPassword)
{
    int userChoice;
    char startNewSession;

    // Loop the prompt until the user decides to exit the application
    do
    {
        printf("Email Client\n");
        printf("1. View Inbox\n");
        printf("2. View Email\n");
        printf("3. Delete Email\n");
        printf("4. Compose Email\n");
        printf("5. View Draft\n");
        printf("6. Logout\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        if (userChoice == 1)
        {
            readInbox(mailServerURL, emailAddress, emailPassword);
        }
        else if (userChoice == 2)
        {
            readEmailByID(outputFileName, mailServerURL, emailAddress, emailPassword);
        }
        else if (userChoice == 3)
        {
            deleteEmailByID(mailServerURL, emailAddress, emailPassword);
        }
        else if (userChoice == 4)
        {
            char destinationEmail[254];
            char emailSubject[100];
            char emailContent[1000];

            composeEmail(destinationEmail, emailSubject, emailContent, mailServerURL, emailAddress, emailPassword);

            // sendEmail(mailServerURL, emailAddress, emailPassword, destinationEmail, emailSubject, emailContent);
        }
        else if (userChoice == 6)
        {
            delete_user_session(outputFileName, mailServerURL, emailAddress, emailPassword);

            printf("Do you want to start a new session? (y/n): ");
            scanf(" %c", &startNewSession);

            if (startNewSession == 'y')
            {
            }
            else if (startNewSession == 'n')
            {
                *continueSession = 0;
            }
        }
        else if (userChoice == 7)
        {
            printf("Exiting application");
            *continueSession = 0;
        }
        else if (userChoice == 5) // View Drafts
        {
            viewDrafts(); // 新增一個函數來顯示草稿
        }

        else
        {
            printf("Invalid choice. Please try again.");
        }

        printf("\n");
    } while (userChoice != 6 && userChoice != 7 && *continueSession);

    curl_global_cleanup();

    printf("\n");
}