#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> 

int execPipe(char*** args ,int nCommands) {

    int p[nCommands - 1][2]; // com 4 comandos criam-se 3 pipes
    int res;
    int status[nCommands];

    for(int i = 0; i < nCommands; i++) { 
        if(i == 0) { //1º filho, só redireciona o stdout
            if(pipe(p[i]) != 0) {
                perror("First pipe not created.");
                return -1;
            }

            switch (fork()) {
                case -1:
                    perror("First fork not made.");
                    return -1;
                    break;
                case 0:
                    //filho é o produtor
                    close(p[i][0]);

                    res = dup2(p[i][1], 1); //o output vai para p[0][1]
                    close(p[i][1]);

                    res = execvp(args[i][0], args[i]);
                    _exit(i);
                    break;
                default:
                    //pai não é consumidor nem produtor
                    close(p[i][1]);
                    break;
            }
        }

        else if(i == nCommands - 1) { //último filho só redireciona o stdout

            switch (fork()) {
                case -1:
                    perror("Last fork not made.");
                    return -1;
                    break;
                case 0:
                    //filho não pode fazer close(p[i - 1][1]);

                    res = dup2(p[i - 1][0], 0); //o output vai para p[0][1]
                    close(p[i - 1][0]);

                    res = execvp(args[i][0], args[i]);
                    _exit(i);
                    break;
                default:
                    //pai
                    close(p[i - 1][0]);
                    break;
            }
        }

        else{ //restantes filhos redirecionam o stdin e o stdout

            if(pipe(p[i]) != 0) {
                perror("Pipe not created.");
                return -1;
            }

            switch (fork()) {
                case -1:
                    perror("Fork not made.");
                    return -1;
                    break;
                case 0:
                    //filho produtor e consumidor
                    close(p[i][0]);
                    
                    res = dup2(p[i - 1][0], 0); //o input vem de p[i - 1][0]
                    close(p[i - 1][0]);
                    res = dup2(p[i][1], 1); //o output vai para p[i][1]
                    close(p[i][1]);

                    res = execvp(args[i][0], args[i]);

                    _exit(i);
                    break;
                default:
                    //pai
                    close(p[i][1]);
                    close(p[i - 1][0]);
                    break;
            }

             
        }
    }

    for(int w = 0; w < nCommands; w++)
        wait(&status[w]);

    return 0;
} 

int main() {
    char* command = strdup("grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l");
    //char* command =strdup("ls -l | wc");

    char*** exec_args = malloc(sizeof(char**)); //matriz em que cada linha é um comando e cada coluna é um argumento

    char* string;
    int l = 0, c = 0;

    char** line;

    while(string != NULL) { 

        line = malloc(sizeof(char*));
        c = 0;
        string = strsep(&command, " ");

        while(c == 0 || (string != NULL && strcmp(string, "|") != 0)) { //copiar um comando
            line = realloc(line, sizeof(char*) * (c + 1));
            line[c] = strdup(string);
            string = strsep(&command, " ");
            c++; //número de argumentos por comando
        }

        line = realloc(line, sizeof(char*) * (c + 1));
        line[c] = NULL;
        c++;

        exec_args = realloc(exec_args, sizeof(char**) * (l + 1));
        exec_args[l] = line;
        l++;    //número de comandos  
    } 

    execPipe(exec_args, l);

    return 0;
}