#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void existe (int** matriz, int linhas, int colunas, int valor) {

    pid_t pid;
    int i = 0, status;

    for(i = 0; i < linhas; i++) { 
        if ((pid = fork()) == 0) {
            //filho
            printf("Filho(%d) - Pid: %d\n", i, getpid());
            printf("Filho(%d) - Pid do pai: %d\n", i, getppid());

            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == valor)
                    _exit(i); //encontrou
            }

            _exit(-1); //não encontrou
        }
    }


    for(i = 0; i < linhas; i++) {
        pid_t terminated_pid = wait (&status);

        if(WIFEXITED(status)) {
            if (WEXITSTATUS(status) < 255) {
                printf("Pai - processo %d terminou. Encontrou o número na linha: %d\n", terminated_pid, WEXITSTATUS(status));
            }
            else
                printf("Pai - processo %d terminou. Não encontrou o número\n", terminated_pid);
            
        }
        else {
            printf("Pai terminou...alguma coisa correu mal\n");
        }
    }
}

int main (int argc, char *argv[]) {

    if(argc < 2) {
        printf("Error - missing value\n");
        return 1;
    }

    int needle = atoi(argv[1]);
    int rows = 10;
    int cols = 10000;
    int rand_max = 10000;
    int **matrix;


    // Allocate and populate matrix with random numbers
    printf("Generating numbers from 0 to %d...\n", rand_max);
    matrix = (int **) malloc(sizeof(int *) * rows);

    for(int i = 0; i < rows; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * cols);

        for(int j = 0; j < cols; j++)
            matrix[i][j] = rand() % rand_max;
    }

    printf("Done.\n");

    existe(matrix,rows,cols,needle);
    
    return 0;
}