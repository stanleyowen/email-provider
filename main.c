// Include the necessary headers
#include <stdio.h>
#include <stdlib.h>

#include "Auth/auth.h"
#include "Auth/session.h"
#include "Layout/base.h"

int main(void)
{   
    // Declare the necessary variables
    char emailAddress[254], emailPassword[128], mailServerURL[500];

    // Declare a variable to continue the session
    _Bool continueSession = 1;

    const char *sessionFileName = "session.txt";
    const char *outputFileName = "output.html";


    // Loop to continue the session until the user decides to exit
    do
    {
        if (login(sessionFileName, mailServerURL, emailAddress, emailPassword, NULL))
        {
            // Print the layout of the email client
            base(&continueSession, outputFileName, sessionFileName, mailServerURL, emailAddress, emailPassword);
        }

    } while (continueSession != 0);

    return 0;
}