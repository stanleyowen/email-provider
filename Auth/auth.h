#ifndef AUTH_H
#define AUTH_H

void authenticate_user_input(char *emailAddress, char *emailPassword, char *accountType, char *mailServer);
void combine_url(char *mailServerURL, char *accountType, char *mailServer);
void save_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL);
void read_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL);

#endif // AUTH_H