#ifndef LAYOUT_H
#define LAYOUT_H

#include <curl/curl.h>

void base(CURL *curl, _Bool *continueSession, const char *outputFileName, char *mailServerURL);

#endif // LAYOUT_H