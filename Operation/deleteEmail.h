#ifndef DELETE_EMAIL_H
#define DELETE_EMAIL_H

#include <curl/curl.h>

void deleteEmailByID(const char *mailServerURL, char *emailAddress, char *emailPassword);

#endif // DELETE_EMAIL_H