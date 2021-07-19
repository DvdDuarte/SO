#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int buffer_size = 10; //dá sempre

    ssize_t read_bytes = 0;
    ssize_t write_bytes = 0;

    char *buffer = malloc(sizeof(char) * buffer_size);

    while ((read_bytes = read (0, buffer, buffer_size)) > 0)
        write_bytes += write (1, buffer, read_bytes);

    close (0);
    close (1);

    free (buffer);

    return write_bytes;
}