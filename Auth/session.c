// Include the necessary headers
#include <stdio.h>
#include <string.h>
#include "auth.h"

// Read the user input from the terminal and save it to a file for maintaining the user session
void save_user_session(const char *filename, char *emailAddress, char *emailPassword, char *mailServer)
{
    // Open the file in write mode
    FILE *file = fopen(filename, "w");

    // Write and save the credentials to the file
    fprintf(file, "%s\n%s\n%s\n", emailAddress, emailPassword, mailServer);
    fclose(file);
}

// Read the user session from the file
void read_user_session(const char *filename, char *emailAddress, char *emailPassword, char *mailServer)
{
    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    // Read the credentials from the file
    fscanf(file, "%s\n%s\n%s\n", emailAddress, emailPassword, mailServer);
    fclose(file);
}

// Delete the user session file and reset the credentials
void delete_user_session(const char *sessionFileName, char *mailServerURL, char *emailAddress, char *emailPassword)
{
    // Reset the email address, password, and mail server URL
    *mailServerURL = ' ';
    *emailAddress = ' ';
    *emailPassword = ' ';

    // Delete the session file
    if (remove("session.txt") != 0)
    {
        perror("Failed to delete the session file, please try again.");
    }
    else
    {
        printf("Logged out successfully.\n");
    }
}