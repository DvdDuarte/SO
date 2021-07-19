#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    int ret;
    pid_t pid;
    int status;

    printf("mensagem 1\n");

    if((pid = fork()) == 0) {
        //filho
        ret = execl("/bin/ls", "/bin/ls", "-l", NULL);

        /* se pusermos aqui o valor 10 por exemplo, o pai vai receber na mesma 0,
        porque execl foi bem sucedido (se for bem sucedido, o filho não executa o que está depois do execl pois
        o programa foi trocado, então o que o pai recebe é o retorno do execl, que é 0 caso corra bem)*/
        _exit(0); 
    }
    else {
        //pai
        pid_t terminated_pid = wait(&status);

        printf("pai: processo %d acabou com o resultado %d\n", terminated_pid, WEXITSTATUS(status));
        printf("mensagem 2\n");
    }

    return 0;
}