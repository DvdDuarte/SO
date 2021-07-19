#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    
    int nFiles = argc - 2;
    int pid;
    int pids[nFiles];

    for(int i = 0; i < nFiles; i++) {

        if((pid = fork()) == 0) {
            execlp("grep", "grep", argv[1], argv[i + 2], NULL);

            exit(0);
        }
        else pids[i] = pid;
    }

    int status;
    int tp;
    int found = 0;

    for(int i = 0; i < nFiles && !found; i++) {
        tp = wait(&status);

        if(WIFEXITED(status)) 
            if(WEXITESTATUS(status) == 0)
                found = 1;

    }

    if (found) {
        for(int f = 0; f < nFiles - 1; f++)
            if(pids[f] != tp && pids[f] > 0)
                kill(pids[f], SIGKILL);
    }
        

    return 0;
}