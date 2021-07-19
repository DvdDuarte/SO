#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main () {

    printf("pid: %d\n", getpid());
    printf("pid pai: %d\n", getppid());

    //sleep(5);

    return 0;
}

//man ps
//ps
//ps -aux
//ps -v

//Ss -- sleep
//R -- running
//Z -- zombie --> enquanto o estado não é recuperado pelo pai