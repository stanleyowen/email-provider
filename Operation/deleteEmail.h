#ifndef DELETE_EMAIL_H
#define DELETE_EMAIL_H

#include <curl/curl.h>

void deleteEmailByID(CURL *curl, const char *mailServerURL);

#endif // DELETE_EMAIL_H