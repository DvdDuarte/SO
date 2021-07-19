#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main() {
    int fd;
    int bytes_read;
    char buffer[BUF_SIZE];

    if((fd = open("fifo", O_RDONLY)) == -1) {
        perror("open reading fifo error");
        return -1;
    }

    printf("Opened fifo for Reading\n");

    while((bytes_read = read(fd, &buffer, BUF_SIZE)) > 0) {
        write(1, &buffer, bytes_read);
    }

    if(bytes_read == 0){
        printf("EOF\n");
    }
    else perror("Reading error\n");

    close(fd);

    return 0;
}