#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {

    pid_t my_pid = getpid();
    pid_t pid_pai = getppid();

    printf("My pid: %d\n", my_pid);
    printf("Pid pai: %d\n\n", pid_pai);

    pid_t pid;
    int i = 1, status;
    int num_processos = 10;

    /* Como não há else, não há código para o pai executar ao mesmo tempo, por isso
    enquanto o filho fica a executar o pai cria logo outro filho. Assim a criação dos filhos é
    sequencial mas a execução deles é paralela. */
    for(i = 1; i <= num_processos; i++) { 
        if ((pid = fork()) == 0) {
            //filho

            printf("Filho(%d) - Pid: %d\n", i, getpid());
            printf("Filho(%d) - Pid do pai: %d\n\n", i, getppid());
            _exit(i);
        }
    }

    for(i = 1; i <= num_processos; i++) {
        pid_t terminated_pid = wait (&status);
        printf("terminated pid: %d -- %d\n\n", WEXITSTATUS(status), terminated_pid);
    }

    printf("Passei aqui\n");
    
    return 0;
}