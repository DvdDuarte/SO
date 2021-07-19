#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char** argv) {

    strcpy(argv[0], "bla"); //mudou o nome do executável
    int ret = execv("ex3", argv);
    
    return 0;
}