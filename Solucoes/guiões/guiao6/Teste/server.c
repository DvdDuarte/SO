#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main() {
    int fd_serverr, fd_serverw; 
    char buffer[BUF_SIZE];
    int bytes_read = 0;

    if((fd_serverr = open("serverr_fifo", O_RDONLY)) == -1) {
        perror("open serverr fifo error");
        return -1;
    }
    if((fd_serverw = open("serverw_fifo", O_WRONLY)) == -1) {
        perror("open serverr fifo error");
        return -1;
    }

    char* texto1 = strdup("Texto1");
    char* texto2 = strdup("texto2,texto2,texto2,texto2,texto2,texto2,texto2,texto2,texto2,texto2,texto2,texto2");

    while((bytes_read = read(fd_serverr, buffer, BUF_SIZE)) > 0) {
        sleep(5);
        if(strcmp(buffer, "status") == 0) write(fd_serverw, texto1, strlen(texto1));
        else write(fd_serverw, texto2, strlen(texto2));
    }

    close(fd_serverr);
    close(fd_serverw);

    return 0;
}