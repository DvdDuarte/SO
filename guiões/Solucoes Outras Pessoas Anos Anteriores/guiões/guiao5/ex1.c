#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>


int pai2filho() {
    int p[2];
    char line[] = "linha1";
    char buffer[20];
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
            //código filho
            close(p[1]);

            res = read(p[0], &buffer, sizeof(buffer));
            printf("[FILHO]: read %s from pipe; res = %d\n", buffer, res);

            close(p[0]);
            _exit(0);
            break;

        default:
            //código pai
            close(p[0]);

            write(p[1], &line, strlen(line));
            printf("[PAI]: wrote line to pipe.\n");

            close(p[1]);
            wait(&status);
            break;
    }

    return 0;
}

int filho2pai() {
    int p[2];
    char line[] = "linha1";
    char buffer[20];
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
            //código filho
            close(p[0]);
    
            write(p[1], &line, strlen(line));
            printf("[FILHO]: wrote line to piper.\n");
    
            close(p[1]);
            _exit(0);
            break;
        
        default:
            //código pai
            close(p[1]);
            res = read(p[0], &buffer, sizeof(buffer));
    
            
            printf("[PAI]: read %s from pipe; res = %d\n", buffer, res);
    
            close(p[0]);
            wait(&status);
            break;
    }

    return 0;
}

int main() {

    pai2filho();
    //filho2pai();

    return 0;
}