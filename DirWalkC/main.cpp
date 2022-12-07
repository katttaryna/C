#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>


#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
static int i = 0;

char ** directory_browsing( char *introducedDir, char *option, int fl, char ** arrayOfFiles)
{
    DIR *dir = NULL;  // поток каталогов

    struct dirent *entry = NULL;
    char pathName[PATH_MAX + 1];
    dir = opendir(introducedDir);
    if( dir == NULL ) {
        printf( "Error opening %s: %s", introducedDir, strerror(errno));
        return 0;
    }
    entry = readdir(dir);
    while(entry != NULL) {
        struct stat entryInfo;
        if((strncmp(entry->d_name, ".", PATH_MAX) == 0) || (strncmp(entry->d_name, "..", PATH_MAX) == 0)) {
            entry = readdir(dir);
            continue;
        }
        (void)strncpy(pathName, introducedDir, PATH_MAX);
        (void)strncat(pathName, "/", PATH_MAX);
        (void)strncat(pathName, entry->d_name, PATH_MAX);
        if(lstat(pathName, &entryInfo) == 0) {
            if(S_ISDIR(entryInfo.st_mode)) {
                if(strstr(option, "d") != NULL || strstr(option, "s") != NULL || fl == 1) {
                    //printf("\t-d %s\n", pathName);
                    arrayOfFiles[i] = strcat(arrayOfFiles[i], "\t-d");
                    arrayOfFiles[i] = strcat(arrayOfFiles[i], pathName);

                    i++;
                    arrayOfFiles = (char**)realloc(arrayOfFiles, (i+1)*sizeof(char*));
                    arrayOfFiles[i] = (char*)calloc(PATH_MAX+20, sizeof (char));
                }
                arrayOfFiles = directory_browsing(pathName, option, fl, arrayOfFiles);
            }
            else if(S_ISREG(entryInfo.st_mode)) {
                if(strstr(option, "f") != NULL || strstr(option, "s") != NULL ||  fl == 1) {

                    arrayOfFiles[i] = strcat(arrayOfFiles[i], "\t-f ");
                    arrayOfFiles[i] = strcat(arrayOfFiles[i], pathName);

                    i++;
                    arrayOfFiles = (char**)realloc(arrayOfFiles, (i+1)*sizeof(char*));
                    arrayOfFiles[i] = (char*)calloc(PATH_MAX+20, sizeof (char));
                    //arrayOfFiles[i] = strcat(arrayOfFiles[i], (long long))
                    //printf("\t-f %s has %lld bytes\n", pathName, (long long)entryInfo.st_size);
                }
            }
            else if(S_ISLNK(entryInfo.st_mode)) {
                char targetName[PATH_MAX + 1];
                if(readlink(pathName, targetName, PATH_MAX) != -1) {
                    if(strstr(option, "l") != NULL || strstr(option, "s") != NULL || fl == 1) {

                        //printf("\t-l %s -> %s\n", pathName, targetName);
                        arrayOfFiles[i] = strcat(arrayOfFiles[i], "\t-l ");
                        arrayOfFiles[i] = strcat(arrayOfFiles[i], pathName);

                        i++;
                        arrayOfFiles = (char**)realloc(arrayOfFiles, (i+1)*sizeof(char*));
                        arrayOfFiles[i] = (char*)calloc(PATH_MAX+20, sizeof (char));
                    }
                }
                else {
                    if(strstr(option, "l") != NULL || fl == 1) {
                        printf("\t%s -> (invalid symbolic link!)\n", pathName);
                    }
                }
            }
        }
        else {
            printf("Error statting %s: %s\n", pathName, strerror(errno));
        }
        entry = readdir(dir);
    }
    (void)closedir(dir);
    return arrayOfFiles;
}

int main(int argc, char **argv)
{   char **arrayOfFiles = (char**)malloc(2*sizeof(char*));
    arrayOfFiles[0] = (char*)malloc((PATH_MAX+20)* sizeof(char));

    char option[PATH_MAX];
    char direct[PATH_MAX];
    int fl;
    if(argc == 3) {
        strncpy(option, argv[2], PATH_MAX);
        strcpy(direct, argv[1]);
        fl = 0;
    }
    if(argc == 1) {
        strcpy(direct,".");
        fl = 1;
    }
    if(argc == 2) {
        if(strstr(argv[1], "-f") != NULL || strstr(argv[1], "-d") != NULL || strstr(argv[1], "-l")
           || strstr(argv[1], "-s") != NULL) {
            strncpy(option, argv[1], PATH_MAX);
            strcpy(direct,".");
            fl = 0;
        }
        else {
            strcpy(direct, argv[1]);
            fl = 1;
        }
    }
    arrayOfFiles = directory_browsing(direct, option, fl, arrayOfFiles );
    if(argc == 2 && strstr(argv[1], "-s") != NULL) {

        for (int a = 0; a < i; a++)
            for (int b = 0; b < i; b++) {
                if (arrayOfFiles[a][2] < arrayOfFiles[b][2]) {
                    char *temp ;
                    temp = arrayOfFiles[a];
                    arrayOfFiles[a] = arrayOfFiles[b];
                    arrayOfFiles[b] = temp;

                }

            }
    }
    if(argc == 3 && strstr(argv[2], "-s") != NULL) {

        for (int a = 0; a < i; a++)
            for (int b = 0; b < i; b++) {
                if (arrayOfFiles[a][2] < arrayOfFiles[b][2]) {
                    char *temp ;
                    temp = arrayOfFiles[a];
                    arrayOfFiles[a] = arrayOfFiles[b];
                    arrayOfFiles[b] = temp;

                }

            }
    }

    //printf("%d ", numberOfFiles);
    for (int a = 0; a < i;a++){
        puts(arrayOfFiles[a]);
    }

    return EXIT_SUCCESS;
}