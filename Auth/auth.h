#ifndef AUTH_H
#define AUTH_H

#include <curl/curl.h>

void authenticate_user_input(char *emailAddress, char *emailPassword, char *accountType, char *mailServer);
void combine_url(char *mailServerURL, char *accountType, char *mailServer, const char *emailID);
void login(CURL *curl, const char *sessionFileName, char *emailAddress, char *emailPassword, char *mailServerURL);

#endif // AUTH_H