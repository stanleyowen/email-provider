#ifndef AUTH_H
#define AUTH_H

void authenticate_user_input(char *emailAddress, char *emailPassword, char *accountType, char *mailServer);
void combine_url(char *url, char *accountType, char *mailServer);

#endif // AUTH_H