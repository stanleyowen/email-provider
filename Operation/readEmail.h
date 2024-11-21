#ifndef READ_EMAIL_H
#define READ_EMAIL_H

#include <curl/curl.h>

void readEmailByID(CURL *curl, const char *outputFileName, char *mailServerURL);
void readInbox(CURL *curl, char *mailServerURL);

#endif // READ_EMAIL_H