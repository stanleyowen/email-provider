#ifndef READ_EMAIL_H
#define READ_EMAIL_H

#include <curl/curl.h>

void readEmailByID(const char *outputFileName, char *mailServerURL, char *emailAddress, char *emailPassword);
void readInbox(char *mailServerURL, char *emailAddress, char *emailPassword);
void previewInboxBeforeDelete(char *mailServerURL, char *emailAddress, char *emailPassword);

#endif // READ_EMAIL_H