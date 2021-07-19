#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int pai2filho() {
    int p[2];
    char* lines[] = {"linha0", "linha1", "linha2", "linha3", "linha4"};
    char buffer;
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
        //fechar extremo de escrita
        close(p[1]);

        while (read(p[0], &buffer, 1) > 0) {
            printf("[FILHO]: read %c from pipe\n", buffer);
        }
        
        //fechar extremo de leitura
        close(p[0]);
        _exit(0);
        break;
    
    default:
        //código pai
        //fechar extremo de leitura
        close(p[0]);

        for(int i = 0; i < 5; i++) {
            write(p[1], lines[i], strlen(lines[i]));
            printf("[PAI]: wrote line: %s to pipe.\n", lines[i]);
        }

        //fechar extremo de escrita
        close(p[1]);

        wait(&status);
        printf("[PAI]: out of wait\n");
        break;
    }

    return 0;
}

int main() {

    pai2filho();

    return 0;
}