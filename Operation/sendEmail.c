#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "auth.h"
#include "deleteEmail.h"

static const char *payload_text =
    "To: <stanley226@sma.belajar.id>\r\n"
    "From: <B11315015@mail.ntust.edu.tw>\r\n"
    "Subject: SMTP example message\r\n"
    "\r\n" /* empty line to divide headers from body, see RFC 5322 */
    "The body of the message starts here.\r\n"
    "\r\n"
    "It could be a lot of lines, could be MIME encoded, whatever.\r\n"
    "Check RFC 5322.\r\n";

struct upload_status
{
    size_t bytes_read;
};

static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp)
{
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data;
    size_t room = size * nmemb;

    if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1))
    {
        return 0;
    }

    data = &payload_text[upload_ctx->bytes_read];

    if (data)
    {
        size_t len = strlen(data);
        if (room < len)
            len = room;
        memcpy(ptr, data, len);
        upload_ctx->bytes_read += len;

        return len;
    }

    return 0;
}

void sendEmail(CURL *curl, char *timestamp, char *destinationEmail, char *emailSubject, char *emailContent)
{
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx = {0};

    // // Modify the URL from pop3 to imap
    // char url[256];
    // strncpy(url, mailServerURL, sizeof(url) - 1);
    // url[sizeof(url) - 1] = '\0'; // Ensure null-termination

    // // Replace the first five characters of the mailServerURL from "pop3s" to "imaps"
    // strncpy(url, "smtps", 5);

    // printf("%s\n", url);

    // Set the CURL options
    curl_easy_setopt(curl, CURLOPT_USERNAME, "B11315015@mail.ntust.edu.tw");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "CKmAT.twU4L2X-w");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<B11315015@mail.ntust.edu.tw>");
    recipients = curl_slist_append(recipients, "<stanley226@sma.belajar.id>");
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail.ntust.edu.tw");

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);

    // Check if the authentication was successful
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else
    {
        curl_slist_free_all(recipients);
        printf("Email sent successfully!\n");
    }
}