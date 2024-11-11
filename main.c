// Include the necessary headers
#include <stdio.h>
#include <curl/curl.h>

int main(void)
{

    /*
     * emailAddress: The email address to use for authentication (https://www.rfc-editor.org/errata/eid1690)
     * emailPassword: The password to use for authentication
     * accountType: The type of account to use for authentication (POP3, IMAP, SMTP)
     * mailServer: The mail server to use for authentication (https://en.wikipedia.org/wiki/Fully_qualified_domain_name)
     * url: The combined account type and mail server to use for authentication
     */
    char emailAddress[254], emailPassword[128], accountType[5], mailServer[255], url[303];

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl)
    {
        // Prompt the user to enter email account information
        printf("Email Address: ");
        scanf("%s", emailAddress);
        printf("Password: ");
        scanf("%s", emailPassword);
        printf("Account Type (POP3 or IMAP): ");
        scanf("%s", accountType);
        printf("Mail Server: ");
        scanf("%s", mailServer);

        // Combine the account type and mail server into a single str with following format: accountType://mailServer
        sprintf(url, "%s://%s", accountType, mailServer);

        printf("Email Address: %s\n", emailAddress);
        printf("Password: %s\n", emailPassword);
        printf("Account Type: %s\n", accountType);
        printf("Mail Server: %s\n", url);

        // /*
        //  * Initialize the CURL object with the necessary options:
        //  * CURLOPT_USERNAME: The username or email to use for authentication
        //  * CURLOPT_PASSWORD: The password to use for authentication
        //  * CURLOPT_URL: The URL of the website to authenticate against
        //  */

        // curl_easy_setopt(curl, CURLOPT_USERNAME, emailAddress);
        // curl_easy_setopt(curl, CURLOPT_PASSWORD, emailPassword);
        // curl_easy_setopt(curl, CURLOPT_URL, url);

        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // res = curl_easy_perform(curl);
        // if (res != CURLE_OK)
        // {
        //     fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        // }
        // else
        // {
        //     printf("Login successful!\n");
        // }

        // curl_easy_cleanup(curl);
    }
    else
    {
        fprintf(stderr, "Failed to initialize CURL.\n");
    }

    return 0;
}