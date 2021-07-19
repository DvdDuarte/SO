#include <unistd.h>
#include <stdio.h>

int main (int argc, char** argv) {

    int ret;
    char *exec_args[] = {"/bin/ls", "-l", NULL};

    printf("mensagem 1\n");

    //ret = execl("/bin/ls", "/bin/ls", "-l", NULL);
    //ret = execlp("ls", "/bin/ls", "-l", NULL);
    //ret = execv("/bin/ls", exec_args);
    ret = execvp("ls", exec_args);


    /* Como o exec substitui o código na main, a "mensagem 2" não é imprimida
    Ele não volta ao processo original.
    Para executar o resto do código, criar um filho com fork e assim o filho executa 
    o exec e o pai imprime "mensagem 2".*/
    printf("mensagem 2\n"); 

    return 0;
}