#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int readC (int fd, char *c) {
    return read(fd,c,1);
}

ssize_t readln (int fd, char *line, size_t size) { // ler tudo de uma vez 
    ssize_t res;
    int i = 0;

    while (i < size && (res = readC(fd, &line[i])) > 0) {
        if (line[i] == '\n') {
            i += res;
            return i;
        }
        i += res;
    } 
    return i;
}

int main (int argc, char *argv[]) {
    
    int buffer_size = 1024; 
    char *buffer = malloc(sizeof(char) * buffer_size);

    char *file;
    if (argv[1] == NULL) 
        file = strdup("my_file");
    else  
        file = strdup(argv[1]);

    int fd = open (file, O_RDONLY);
    ssize_t read_bytes = readln(fd,buffer,buffer_size);

    close(fd);

    printf("\nForam lidos %lu bytes\nA linha: %s\n", read_bytes, buffer);

    free (buffer); 

    return 0;
}