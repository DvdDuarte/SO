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

//Esta função põe em *c sempre apenas um caracter. 

//Caso read_buffer_pos e read_buffer_end apontem para o mesmo sítio, quer por
//termos lido o buffer todo ou por estarmos a ler pela primeira vez, lemos 
//do ficheiro 512 chars de uma vez. Caso dê erro mostramos que deu erro, 
//caso não dê erro colocamos read_buffer_pos a 0 para dizermos que temos 512
//chars novos para ler.

//Quando já temos algo no buffer e ainda não lemos tudo, lemos apenas o próximo
//char do buffer e colocamos em *c. Retornamos a dizer que lemos um char.
int readAll (int fd, char *c) {
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

ssize_t readln (int fd, char *buf, size_t size) { // ler tudo de uma vez 
    ssize_t read_bytes = 0;
    int i = 0;

    while (i < size && (read_bytes = readAll(fd, &buf[i]) > 0)) {
        if (buf[i] == '\n') {
            i += read_bytes;
            return i;
        }
        i += read_bytes;
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