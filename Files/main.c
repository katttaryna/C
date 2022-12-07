#include "header.h"
#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = NULL;
    int action;
    printf("Enter the file name:\n");
    rewind(stdin);
    char str[20];
    fgets(str, 20, stdin);
    rewind(stdin);
    str[strlen(str) - 1] = '\0';
    printf("Select an action:\n"
           "1. Work with a text file (.txt)\n"
           "2. Work with a binary file (.bin)\n"
           "0. Exit\n");
    action=inputSave(0 , 2 );
    rewind(stdin);
    switch (action) {
        case 1 :
            actionsWithATextFile(str);
            break;
        case 2 :
            actionsWithABinFile(str);
            break;
        case 0 :

            return 0;
        default:
            printf("Error. Incorrect value!\n");
    }
    fclose(file);
    return 0;
}
