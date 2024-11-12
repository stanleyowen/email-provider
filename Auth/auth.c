// Include the necessary headers
#include <stdio.h>
#include <string.h>
#include "auth.h"

/*
 * emailAddress: The email address to use for authentication (https://www.rfc-editor.org/errata/eid1690)
 * emailPassword: The password to use for authentication (https://stackoverflow.com/questions/98768/should-i-impose-a-maximum-length-on-passwords)
 * accountType: The type of account to use for authentication (POP3, IMAP, SMTP)
 * mailServer: The mail server to use for authentication (https://en.wikipedia.org/wiki/Fully_qualified_domain_name)
 * url: The combined account type and mail server to use for authentication
 */
void authenticate_user_input(char *emailAddress, char *emailPassword, char *accountType, char *mailServer)
{
    printf("Email Address: ");
    scanf("%254s", emailAddress);
    printf("Password: ");
    scanf("%128s", emailPassword);
    printf("Account Type (POP3 or IMAP): ");
    scanf("%5s", accountType);
    printf("Mail Server: ");
    scanf("%255s", mailServer);
}

/*
 * url: The combined account type and mail server to use for authentication in the format accountType://mailServer
 * Example: pop3://mail.ntust.edu.tw
 */
void combine_url(char *mailServerURL, char *accountType, char *mailServer)
{
    sprintf(mailServerURL, "%s://%s", accountType, mailServer);
}

// Read the user input from the terminal and save it to a file for maintaining the user session
void save_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL)
{
    // Open the file in write mode
    FILE *file = fopen("session.txt", "w");

    // Write and save the credentials to the file
    fprintf(file, "%s\n%s\n%s\n%s\n", emailAddress, emailPassword, accountType, mailServerURL);
    fclose(file);
}

// Read the user session from the file
void read_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL)
{
    // Open the file in read mode
    FILE *file = fopen("session.txt", "r");

    // Read the credentials from the file
    fscanf(file, "%s\n%s\n%s\n%s\n", emailAddress, emailPassword, accountType, mailServerURL);
    fclose(file);
}