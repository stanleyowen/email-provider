#ifndef COMPOSE_EMAIL_H
#define COMPOSE_EMAIL_H

#include <curl/curl.h>

void composeEmail(char *destinationEmail, char *emailSubject, char *emailContent, char *mailServerURL, char *emailAddress, char *emailPassword);

#endif // COMPOSE_EMAIL_H