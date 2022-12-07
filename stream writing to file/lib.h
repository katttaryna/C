#include <aio.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



#define BUFFER_SIZE 1024


bool readAccess = true, writeAccess = false;
int byte;
int offset;
struct aiocb *list;
int n = 3;
char *buffer, **files;

void endRead(int sig){


    writeAccess = true;

}

void endCopy(int sig){

    readAccess = true;

}

void* readFile(){
    for(int i = 0; i < 3; i++) {

        while(!readAccess) { }

        readAccess = false;

        buffer = malloc(BUFFER_SIZE);

        list = malloc(sizeof(struct aiocb));

        struct stat info;
        stat (files[i], &info);
        byte = info.st_size;

        list -> aio_fildes  = open(files[i], O_RDONLY);
        list -> aio_buf     = (void*)buffer;
        list -> aio_nbytes  = byte;
        list -> aio_reqprio = 0;
        list -> aio_offset  = 0;
        list -> aio_sigevent.sigev_notify = SIGEV_SIGNAL;
        list -> aio_sigevent.sigev_signo  = SIGUSR1;

        aio_read(list);


    }

}

void* writeFile(void *arg){
    int num = n, write_bytes = 0;
    struct aiocb *asyncWriteRead;

    int count = 0;
    struct stat info;

    write_bytes  = 0;

    while(num > 0) {

        while(!writeAccess) {};

        writeAccess = false;

        char* temp = (char*)malloc(BUFFER_SIZE*sizeof(char));

        strcpy(temp, buffer);


        kill(getpid(), SIGUSR2);
        asyncWriteRead = malloc(sizeof(struct aiocb));
        asyncWriteRead -> aio_fildes  = open("result.txt", O_RDWR | O_CREAT);
        asyncWriteRead -> aio_reqprio = 0;
        asyncWriteRead -> aio_offset  = 0;
        asyncWriteRead -> aio_sigevent.sigev_notify = SIGEV_NONE;

        stat (files[count], &info);
        int size = info.st_size;

        asyncWriteRead -> aio_buf    = (void*)temp;
        asyncWriteRead -> aio_nbytes = strlen(temp);
        asyncWriteRead -> aio_offset = offset;

        aio_write(asyncWriteRead);
        offset += size;
        num--;
        count++;
    }

    return NULL;
}

void start(){

    struct sigaction sa;

    files    = malloc(3 * sizeof(char*));
    files[0] = malloc(2*sizeof(char));
    files[1] = malloc(2*sizeof(char));
    files[2] = malloc(2*sizeof(char));
    strcpy(files[0], "1");
    strcpy(files[1], "2");
    strcpy(files[2], "3");

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = endRead;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = endCopy;
    sigaction(SIGUSR2, &sa, NULL);

}