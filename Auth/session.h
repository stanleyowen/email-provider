#ifndef SESSION_H
#define SESSION_H

void save_user_session(const char *fileName, char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL);
void read_user_session(const char *fileName, char *emailAddress, char *emailPassword, char *accountType, char *mailServerURL);

#endif // SESSION_H