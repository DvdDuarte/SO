#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "pessoas.h"

int main(int argc, char const *argv[]) {

    if (argc < 4) {
        printf("ERROR - Wrong number of arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0) acrescentaPessoa (argv[2], atoi(argv[3]));
    else if (strcmp(argv[1], "-u") == 0) atualizaIdade (argv[2], atoi(argv[3]));
    else printf("ERROR - Invalid mode.\n");
    
    imprimePessoas();
    
    return 0;
} 


