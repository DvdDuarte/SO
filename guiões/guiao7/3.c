#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> 



int* pids;
int npids;
int sec;

void handler_alarm(int signum) {
    for(int i = 0; i < npids; i++) {
        ////////////////FALLLLLLLLLLLLLTTTTTTTTTAAAAAAAAAAAMMMMMMMM COISAS AQUI E VERIFICAR A MAIN
    }
    sec = 1;
}