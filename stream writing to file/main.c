#include "lib.h"
#include <string.h>
#include <pthread.h>

int main(){


    pthread_t pid;
    pthread_create(&pid, NULL, writeFile, NULL);

    start();
    readFile();

    pthread_join(pid, NULL);

    return 0;
}
