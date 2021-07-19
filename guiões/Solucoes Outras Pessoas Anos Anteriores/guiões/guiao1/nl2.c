#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024
#define MAX_READ_BUFFER 512
char read_buffer[MAX_READ_BUFFER];
int read_buffer_pos = 0;
int read_buffer_end = 0;

//Ler um Char de forma EFICIENTE (ler do ficheiro apenas 1 vez).
int readC (int fd, char *c) {
    if (read_buffer_pos == read_buffer_end) {

        read_buffer_end = read(fd,read_buffer,MAX_READ_BUFFER);

        switch (read_buffer_end) {
            case -1:
                printf("Error");
                return -1;
            case 0: //não leu nada, chegou ao EOF
                return 0;
            default:
                read_buffer_pos = 0;
                break;
            }
    }
    *c = read_buffer[read_buffer_pos++];
    return 1;
}

ssize_t readln (int fd, char *line, size_t size) { // ler tudo de uma vez 
    ssize_t read_bytes = 0;
    int i = 0;

    while (i < size && (read_bytes = readC(fd, &line[i]) > 0)) {
        if (line[i] == '\n') {
            i += read_bytes;
            return i;
        }
        i += read_bytes;
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
    char *buffer = malloc(sizeof(char) * MAX_SIZE);

    int lcounter = 0;
    int newline = 1;

    while ((res = readln(fd, buffer, MAX_SIZE)) > 0) {
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