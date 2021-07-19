#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char** argv) {

    for(int i = 0; i < argc; i++) {
        write(1, argv[i], strlen(argv[i]));
        write(1, "\n", 1);
    }
    
    return 0;
}

//gcc ex3.c -o ex3 ---> cria o executável chamado ex3