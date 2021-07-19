#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ctrl_c = 0;
int sec = 0;

void handler_quit (int signum) {
    printf("Pressed Ctrl+c: %d times\n", ctrl_c);
    exit(0);
}

void handler_alarm(int signum) {
    sec++;
}

void handler_ctrl_c (int signum) {
    ctrl_c++;
    printf("Time: %d\n", sec);
}

int main () {
    printf("Pid: %d\n", getpid());
    
    signal(SIGINT, handler_ctrl_c);
    signal(SIGALRM, handler_alarm);
    signal(SIGQUIT, handler_quit);
    
    while (1) {
        alarm(1);
        pause();
    }

    return 0;
}

//para funcionar imprimir o pid no ecrã e fazer o kill (kill -SIGINT pid..) num terminal ao lado e depois (kill -SIGQUIT pid...)

/* Forma alternativa para que o programa continue a contar os segundos de forma correta mesmo quando alguém faz muitas vezes ctrl-c

void handler_alarm(int signum) {
    sec++;
    alarm(1);
}

int main () {
    printf("Pid: %d\n", getpid());
    
    signal(SIGINT, handler_ctrl_c);
    signal(SIGALRM, handler_alarm);
    signal(SIGQUIT, handler_quit);
    
    while (1) {
        pause();
    }

    return 0;
}

*/