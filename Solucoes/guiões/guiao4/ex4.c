#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

//int system (const char* command)
//retorna -1 se o fork falha ou o valor do comando executado
int mysystem(char* command) {

    int fork_ret,  exec_ret, wait_ret, status, res;

    char*exec_args[20]; //estamos a assumir um número máximo de argumentos
    char *string;
    int i = 0;

    string = strtok(command, " ");

    while(string != NULL) {

        exec_args[i] = string;
        string = strtok(NULL, " ");
        i++;
    }
    //exec_agrs -> ["ls", "-l", "-a", "-h", NULL]
    exec_args[i] = NULL;

    fork_ret = fork();

    if(fork_ret == 0) {

        exec_ret = execvp(exec_args[0], exec_args);
        _exit(exec_ret);
    }
    else {
        if (fork_ret != -1) {

            wait_ret = waitpid(fork_ret, &status, 0);

            if(WIFEXITED(status))
                res = WEXITSTATUS(status);
            else
                res = -1;
        }
        else
            res = -1;
    }

    return res;
}


int main (int argc, char* argv[]) {
    int res = 0;
    int commandindex = 1;
    char command[1024];
    int input_fd, output_fd;

    bzero(command, 1024); //--> põe a 0 o command todo
    setbuf(stdout, NULL);

    if(strcmp(argv[commandindex], "-i") == 0) {
        int input_fd = open(argv[commandindex + 1], O_RDONLY);
        res = dup2(input_fd, 0);
        close(input_fd);

        commandindex + 2;
    }

    if(strcmp(argv[commandindex], "-o") == 0) {
        int output_fd = open(argv[commandindex + 1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
        res = dup2(output_fd, 1);
        close(output_fd);

        commandindex + 2;
    }

    while(commandindex < argc) {
        strcat(command, argv[commandindex]);
        strcat(command, " ");

        commandindex++;
    }

    mysystem(command);

    return 0;
}

//exercício adicional >> (append - ficheiro já criado)