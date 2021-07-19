#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int fd = open ("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    size_t res = 0;

    char *buffer = malloc(sizeof(char) * 1024);
    for (int i = 0; i < 1024; i++)
        buffer[i] = 'a';

    res = write (fd, buffer, 1024);

    close (fd);
    free (buffer);

    return res;
}