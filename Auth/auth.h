#ifndef AUTH_H
#define AUTH_H

#include <curl/curl.h>

void authenticate_user_input(char *emailAddress, char *emailPassword, char *mailServer);
void combine_url(char *mailServerURL, char *accountType, char *mailServer, char *emailID);
int login(const char *sessionFileName, char *mailServerURL, char *emailAddress, char *emailPassword, char *null);

#endif // AUTH_H