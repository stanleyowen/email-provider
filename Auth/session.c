// Include the necessary headers
#include <stdio.h>
#include <string.h>
#include "auth.h"

// Read the user input from the terminal and save it to a file for maintaining the user session
void save_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServer)
{
    // Open the file in write mode
    FILE *file = fopen("session.txt", "w");

    // Write and save the credentials to the file
    fprintf(file, "%s\n%s\n%s\n%s\n", emailAddress, emailPassword, accountType, mailServer);
    fclose(file);
}

// Read the user session from the file
void read_user_session(char *emailAddress, char *emailPassword, char *accountType, char *mailServer)
{
    // Open the file in read mode
    FILE *file = fopen("session.txt", "r");

    // Read the credentials from the file
    fscanf(file, "%s\n%s\n%s\n%s\n", emailAddress, emailPassword, accountType, mailServer);
    fclose(file);
}