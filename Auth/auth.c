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
    printf("Email Address\t\t\t: ");
    scanf("%254s", emailAddress);

    printf("Password\t\t\t: ");
    scanf("%128s", emailPassword);

    printf("Account Type (POP3 or IMAP)\t: ");
    scanf("%5s", accountType);

    printf("Mail Server\t\t\t: ");
    scanf("%255s", mailServer);
}

/*
 * url: The combined account type and mail server to use for authentication in the format accountType://mailServer
 * Example: pop3://mail.ntust.edu.tw
 */
void combine_url(char *mailServerURL, char *accountType, char *mailServer)
{
    sprintf(mailServerURL, "%s://%s/INBOX/;UID=1", accountType, mailServer);
}