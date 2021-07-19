#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> 

// ./a.out "ola" file1.txt file2.txt file3.txt
int main(int argc, char *argv[]) { //multigrep "palavra" fich1.txt fich2.txt fich3.txt ...

    int filhos = argc - 2;
    char** args = argv;

    int res, status;
    int pids[filhos];
    int pid;

    for(int i = 0; i < filhos; i++) {

        pid = fork();
        switch (pid) {
                case -1:

                    perror("Fork not made.");
                    return -1;

                    break;
                case 0:
                    pids[i] = getpid();

                    if ((res = execlp("grep", "grep", args[1], args[i + 2], NULL)) < 0) {
                        perror("exec");
                    }

                    _exit(res);
                    break;
                default:
                    printf("Filho %d executing grep %s %s\n", pid, args[1], args[i + 2]);
                    break;
            }
    }

    int found = 0;
    pid_t terminated_pid;

    for(int j = 0; j < filhos && !found; j++) {
        terminated_pid = wait(&status);

        if(WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                printf("Pai - processo %d terminou. Encontrou a palavra.\n", terminated_pid);
                found = 1;
            }
            else
                printf("Pai - processo %d terminou. Não encontrou a palavra\n", terminated_pid);
        }  
    }

    if (found) {
        for(int f = 0; f < filhos - 1; f++) 
            if(pids[f] != terminated_pid && pids[f] > 0)
                res = kill(pids[f],SIGKILL);
    }

    return 0;
}