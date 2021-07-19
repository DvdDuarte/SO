#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUF_SIZE 1024

int main() {
    int fd;
    int bytes_read;
    char buffer[BUF_SIZE];

    printf("Tamanho do pipe em memória: %d\n", PIPE_BUF); 

    if((fd = open("fifo", O_WRONLY)) == -1) {
        perror("open write fifo error");
        return -1;
    }

    printf("Opened fifo for Writing\n");

    while((bytes_read = read(0, buffer, BUF_SIZE)) > 0) {
        if(write(fd, buffer, bytes_read) == -1)
            perror("Writing error");
    }

    close(fd);

    return 0;
}