#include<stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int ctrl_c_counter;

void ctrl_c_handler(int signum) {
    printf("CTRL+C\n");
    ctrl_c_counter++;
}

int main(int agrc, char* argv[]) {

    if(signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
        perror("SIGINT failed");
    }

    while(ctrl_c_counter < 3) {
        printf("working...\n");
        sleep(1);
    }

    return 0;
}