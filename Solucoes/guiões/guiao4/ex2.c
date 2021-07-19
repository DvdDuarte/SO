#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
    int res = 0;

    int input_fd = open("/etc/passwd", O_RDONLY);
    int output_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_fd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    //se quiser imprimir no stout? (passo 1)
/*    int fdin = dup(0);
    int fdout = dup(1);
    int fderr = dup(2); */

    res = dup2(input_fd, 0);
    res = dup2(output_fd, 1);
    res = dup2(error_fd, 2);

    close(input_fd);
    close(output_fd);
    close(error_fd);

    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        int read_res;
        char buffer;
        char line[1024];
        int i = 0;
        while((read_res = read(0, &buffer, 1)) != 0) {
            line[i] = buffer;
            i++;
            if(buffer == '\n') {
                write(1, line, i);
                write(2, line, i);

                i = 0;
            }
        }

        _exit(0);
    }
    else {
        pid_t terminated_pid = wait(&status);


        //se quiser imprimir no stout? (passo 2)
    /*    dup2(fdin,0);
        dup2(fdout,1);
        dup2(fderr,2);

        close(fdin);
        close(fdout);
        close(fderr); */

        if(WIFEXITED(status)) { //saiu com sucesso
            printf("O filho retornou %d\n", WEXITSTATUS(status)); //esta frase só é escrita no saida.txt porque foi o output redirecionado
        } 
        else printf("O filho não terminou\n");
    }

    return 0;
}

