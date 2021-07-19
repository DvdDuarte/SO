#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd; 

    if((fd = open("fifo", O_WRONLY)) == -1) {
        perror("open write fifo error");
        return -1;
    }

    printf("Opened fifo for Writing\n");

    if (write(fd, argv[1], strlen(argv[1])) == -1) {
        perror("Writing fifo error");
    }

    close(fd);

    return 0;
}