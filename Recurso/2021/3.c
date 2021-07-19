#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_EXEC 100 
#define TIME_LIMIT 20

int isRound = 1;
int normal_exit = 0;
int pids[N_EXEC];

void timeout_handler() {
	
	for(int i = 0; i < N_EXEC; i++){
		if(pids[i] > 0);
		kill(pids[i], SIGKILL);
	}

	printf("Normal exits; %d\n", normal_exit);
	exit(0);

}

void sigint_handler(int signum) {

	isRound = 0;

	for(int i = 0; i < N_EXEC; i++){
		if(pids[i] > 0);
		kill(pids[i], SIGKILL);
	}
	
	printf("\nNormal exits: %d\n", normal_exit);
	exit(1);

}

int main(){

	if(signal(SIGALRM, timeout_handler) == SIG_ERR) {
		perror("signal alarm");
		exit(1);
	}

	if(signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal sigint");
		exit(1);
	}

	while(isRound) {

	alarm(TIME_LIMIT);

	for(int i = 0; i < N_EXEC; i++){
		if((pids[i] = fork()) == 0) {

			execlp("grep", "grep", "\"COCKPIT\"", "beeMovieScript.txt",NULL);
			perror("Execlp cmd");
			_exit(1);

		}
	}

	int status;

	for(int i = 0; i < N_EXEC; i++){
		wait(&status);
		if(WEXITSTATUS(status) == 0 || WEXITSTATUS(status) == 1)
			normal_exit++;
	}

	printf("Normal exits: %d\n", normal_exit);

	}

    return 0;


}