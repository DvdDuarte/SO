#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int fd_serverr, fd_serverw; 

    if((fd_serverr = open("serverr_fifo", O_WRONLY)) == -1) {
        perror("open serverr fifo error");
        return -1;
    }
    if((fd_serverw = open("serverw_fifo", O_RDONLY)) == -1) {
        perror("open serverr fifo error");
        return -1;
    }

    write(fd_serverr, argv[1], strlen(argv[1]));

    char* buffer = malloc(sizeof(1024));
    read(fd_serverw, buffer, sizeof(char) * 1024);

    write(1,buffer, strlen(buffer));

    close(fd_serverr);
    close(fd_serverw);

    return 0;
}