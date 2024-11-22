#ifndef COMPOSE_EMAIL_H
#define COMPOSE_EMAIL_H

#include <curl/curl.h>

void composeEmail(char *destinationEmail, char *emailSubject, char *emailContent);

#endif // COMPOSE_EMAIL_H