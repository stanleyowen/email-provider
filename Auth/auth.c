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
void combine_url(char *url, char *accountType, char *mailServer)
{
    sprintf(url, "%s://%s", accountType, mailServer);
}