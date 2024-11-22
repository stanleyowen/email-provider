
#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

#include <curl/curl.h>

void sendEmail(CURL *curl, char *mailServerURL, char *timestamp, char *destinationEmail, char *emailSubject, char *emailContent);

#endif // SEND_EMAIL_H