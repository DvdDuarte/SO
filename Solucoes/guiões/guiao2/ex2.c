#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {

    pid_t pid;
    int i = 0, status;

    if ((pid = fork()) == 0) {
        //filho

        //sleep(3);

        //i++;
        //printf("filho %d\n", i);
        printf("filho - pid: %d\n", getpid());
        printf("filho - pid pai: %d\n", getppid());

        _exit(0);
    }
    else {
        //pai

        //sleep(2);

        //i--;
        //printf("pai %d\n", i);
        
        //pid_t terminated_pid = wait (&status);
        //printf("\nterminated pid: %d -- %d\n", WEXITSTATUS(status), terminated_pid);

        printf("pai - pid do filho: %d\n", pid);
        printf("pai - pid: %d\n", getpid());
        printf("pai - pid pai: %d\n", getppid());
    }
    
    return 0;
}
