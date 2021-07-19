#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

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

    char *file;
    if (argv[1] == NULL) 
        file = strdup("my_file");
    else  
        file = strdup(argv[1]);

    int fd = open (file, O_RDONLY);

    int res = 0;
    char *buffer = malloc(sizeof(char) * MAX_BUFFER);

    int lcounter = 0;
    int newline = 1;

    while ((res = readln(fd, buffer, MAX_BUFFER)) > 0) {
        char line_number[10] = "";
    
        if (newline && buffer[0] != '\n') { //nl skips empty lines
            snprintf(line_number, 10, "%d: ", lcounter); //escreve em line_number o número da linha
            write(1,line_number,sizeof(line_number));
            lcounter++;
        }

        write(1,buffer,res);

        if (buffer[res - 1] != '\n')
            newline = 0;
        else
            newline = 1;
    }

    close(fd);
    free(buffer);
        
    return 0;
}