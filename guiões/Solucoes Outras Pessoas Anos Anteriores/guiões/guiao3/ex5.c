#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {
    int fork_ret, exec_ret, i;

    for(i = 1; i < argc; i++) {

        fork_ret = fork();

        if(fork_ret == 0) {
            printf("filho - %d e vou executar o comando - %s\n\n", getpid(), argv[i]);


            exec_ret = execlp(argv[i], argv[i], NULL);

            perror("reached return");

            _exit(exec_ret);
        }
    }

    for(i = 1; i < argc; i++) {
       //printf("pai à espera de um filho...\n");
        wait(NULL);
    }

    printf("\n\ntodos os filhos executaram\n");

    return 0;
}