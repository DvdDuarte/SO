#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUF_SIZE 1024

int main() {
    int fdLog; 
    int fdFifo;
    char buffer[BUF_SIZE];
    int bytes_read = 0;

    if((fdLog = open("log.txt", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0666)) == -1) {
        perror("open log error");
        return -1;
    }

    bzero(buffer, BUF_SIZE);
    while(1) {
        if((fdFifo = open("fifo", O_RDONLY)) == -1) {
            perror("open fifo for reading");
            return -1;
        }

        while((bytes_read = read(fdFifo, buffer, BUF_SIZE)) > 0) {
            write(fdLog, buffer, bytes_read);
            write(fdLog, "\n", 1);
            bzero(buffer, BUF_SIZE);
        }

        if(bytes_read == 0){
            printf("EOF\n");
        }
        else perror("Reading error\n");
    }

    close(fdLog);
    close(fdFifo);

    return 0;
}