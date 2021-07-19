#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int buffer_size = 10;

    int fd_read = open ("tmp_file", O_RDONLY); //open (argv[2], O_RDONLY); 
    int fd_write = open ("tmp_file_copy", O_CREAT | O_TRUNC | O_WRONLY, 0700);

    ssize_t read_bytes = 0;
    ssize_t write_bytes = 0;

    char *buffer = malloc(sizeof(char) * buffer_size);

    while ((read_bytes = read (fd_read, buffer, buffer_size)) > 0)
        write_bytes += write (fd_write, buffer, read_bytes);

    close (fd_read);
    close (fd_write);

    free (buffer);

    printf("Copied bytes %ld bytes\n", write_bytes);

    return write_bytes;
}