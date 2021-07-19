#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() { 
    int p[2];
    int res;
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

            res = execlp("wc", "/bin/wc", "-l", NULL);
            
            _exit(0);
            break;

        default:
            //código pai - produtor
            //fechar extremo de leitura
            close(p[0]);

            res = dup2(p[1], 1);
            close(p[1]);

            res = execlp("ls", "ls", "/etc", NULL);            

            wait(&status);
            break;
    }
    return 0;
}