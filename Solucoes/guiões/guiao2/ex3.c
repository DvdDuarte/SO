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
    int num_proc = 10;

    while (i <= num_proc) {
        if ((pid = fork()) == 0) {
        //filho

        printf("Filho - Pid: %d\n", getpid());
        printf("Filho - Pid do pai: %d\n", getppid());
        //sleep(1);
        _exit(i);
        }
        else {
            //pai
            
            pid_t terminated_pid = wait (&status);
            printf("terminated pid: %d -- %d\n\n", WEXITSTATUS(status), terminated_pid);

        }
        i++;
    }

    printf("Passei aqui\n");
    
    return 0;
}