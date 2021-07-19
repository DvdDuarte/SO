#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_SIZE 1024
#define MAX_READ_BUFFER 512
char read_buffer[MAX_READ_BUFFER];
int read_buffer_pos = 0;
int read_buffer_end = 0;

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

ssize_t readln (int fd, char *buf, size_t size) { 
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

int wcPipe() {
    int p[2];
    int status;

    if(pipe(p) == -1) {
        perror("Pipe not created.");
        return -1;
    }

    switch (fork()) {
        case -1:
            perror("Fork not made.");
            return -1;
            break;
        case 0:
            //código filho - consumidor
            //fechar extremo de escrita
            close(p[1]);

            dup2(p[0], 0);
            close(p[0]);

            execlp("wc", "/bin/wc", NULL);
            
            _exit(0);
            break;

        default:
            //código pai - produtor
            //fechar extremo de leitura
            close(p[0]);

            char *buffer = malloc(sizeof(char) * MAX_SIZE);

            ssize_t read_bytes;
            while((read_bytes = readln(0, buffer, MAX_SIZE)) > 0) {
                write(p[1], buffer, read_bytes);
            }

            free (buffer); 

            //fechar extremo de escrita
            close(p[1]);

            wait(&status);
            break;
    }
    return 0;
}

int main() {
    wcPipe();
    return 0;
}