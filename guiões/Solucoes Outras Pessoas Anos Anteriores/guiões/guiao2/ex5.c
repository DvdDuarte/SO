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

    for(i = 1; i <= num_processos; i++) { 
        if ((pid = fork()) == 0) {

            printf("Filho(%d) - Pid: %d\n", i, getpid());
            printf("Filho(%d) - Pid do pai: %d\n\n", i, getppid());
        }
        else {
            pid_t terminated_pid = wait (&status);

            if (WIFEXITED(status)) {
                printf("terminated pid: %d -- %d\n\n", WEXITSTATUS(status), terminated_pid);
            }
            else {
                printf("Pai process %d exited.\n", terminated_pid);
            }
            _exit(i);
        }
    }

    printf("Saí ciclo pid %d\n", getpid());
    _exit(0);

    printf("Passei aqui\n");
    
    return 0;
}