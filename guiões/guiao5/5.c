#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int execcommands (char *command) { 

	char *aux[10];
	int i = 0;
	char* comando = strdup(command);
	
	while(command != NULL) {

		aux[i] = strtok(command," ");
		i++;
	}

	aux[i] = NULL;

	int resp;

	resp = execvp(aux[0], aux);
	exit(1);

	return resp;

}

int main(int argc, char const *argv[]) {
	int pipe_fd[3][2];

	if(pipe(pipe_fd[0]) < 0) {
		perror("pipe");
		exit(1);
	}

	char* commands[] = {"grep -v ˆ# /etc/passwd", "cut -f7 -d:","uniq", "wc -l"};

	if(fork() == 0) {
		close(pipe_fd[0][0]);
		dup2(pipe_fd[0][1], 1);
		close(pipe_fd[0][1]);
		execcommands(commands[0]);
		_exit(1);
	}

	close(pipe_fd[0][1]);

	if(pipe(pipe_fd[1]) < 0) {
		perror("pipe");
		exit(1);
	}	

	if(fork() == 0) {
		close(pipe_fd[1][0]);

		dup2(pipe_fd[0][0],0);
		close(pipe_fd[0][0]);
		dup2(pipe_fd[1][1], 1);
		close(pipe_fd[1][1]);
		execcommands(commands[1]);
		_exit(1);
	}

	close(pipe_fd[0][0]);
	close(pipe_fd[1][1]);

	if(pipe(pipe_fd[2]) < 0) {
		perror("pipe");
		exit(1);
	}

	if(fork() == 0) {
		close(pipe_fd[2][0]);

		dup2(pipe_fd[1][0],0);
		close(pipe_fd[1][0]);
		dup2(pipe_fd[2][1], 1);
		close(pipe_fd[2][1]);
		execcommands(commands[2]);
		_exit(1);
	}

	close(pipe_fd[1][0]);
	close(pipe_fd[2][1]);

	if(fork() == 0) {
		dup2(pipe_fd[2][0], 0);
		close(pipe_fd[2][0]);
		execcommands(commands[3]);
		_exit(1);
	}

	int status;

	for(int i = 0; i < 4; i++) {
		wait(&status);
	}

	return 0;
}

