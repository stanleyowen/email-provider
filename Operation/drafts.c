#include <stdio.h>
#include <string.h>
#include "drafts.h"

// Save the email draft
void saveDraft(const char *destinationEmail, const char *emailSubject, const char *emailContent)
{
    FILE *file = fopen("drafts.txt", "a"); // Append mode to save new drafts
    if (file != NULL)
    {
        fprintf(file, "To: %s\nSubject: %s\n%s\n\n", destinationEmail, emailSubject, emailContent);
        fclose(file);
        printf("Draft saved successfully!\n");
    }
    else
    {
        printf("Failed to save draft.\n");
    }
}

// View saved drafts
void viewDrafts(void)
{
    FILE *file = fopen("drafts.txt", "r");
    if (file != NULL)
    {
        char line[1024];
        printf("\n----- Saved Drafts -----\n");
        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
        fclose(file);
    }
    else
    {
        printf("No drafts found.\n");
    }
}