
#ifndef SEND_EMAIL_H
#define SEND_EMAIL_H

#include <curl/curl.h>

void sendEmail(char *mailServerURL, char *emailAddress, char *emailPassword, char *destinationEmail, char *emailSubject, char *emailContent);

#endif // SEND_EMAIL_H