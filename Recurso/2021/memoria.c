#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_EXEC 10
#define BUFFER_SIZE 1024

int main(int argc, char * argv[]) { 

	if(argc < 2) {
		perror("Arguments");
		exit(1);
	}


	int count[N_EXEC];

	for(int i = 0; i < N_EXEC; i++) {

		pid_t pid;

		if((pid = fork()) == 0){

			execvp(argv[1], argv + 1); //argv = memoria ls -la
			perror("Execvp");
			_exit(1);

		}

		int pipe_fd[2][2];
		if(pipe(pipe_fd[0]) < 0) {
			perror("Pipe 1 creation failed");
			exit(1);
		}

		char * pid_string = malloc(BUFFER_SIZE);

		if(fork() == 0) {

			close(pipe_fd[0][0]);
			dup2(pipe_fd[0][1], 1);
			close(pipe_fd[0][1]);

			snprintf(pid_string, BUFFER_SIZE, "proc/%d/memstats", pid);
			execlp("grep", "grep", "vmPeak", pid_string, NULL);
			perror("Execlp Grep");
			_exit(1);
		}

		free(pid_string);
		close(pipe_fd[0][1]);

		if(pipe(pipe_fd[1]) < 0) {
			perror("Pipe 2 creation failed");
			exit(1);
		}

		if(fork() == 0){

			close(pipe_fd[0][1]);
			close(pipe_fd[1][0]);

			dup2(pipe_fd[0][0], 0);
			close(pipe_fd[0][0]);
			dup2(pipe_fd[1][1], 1);
			close(pipe_fd[1][1]);

			execlp("cut", "cut", "-d" "", "-f4", NULL);
			perror("Execlp Cut");
			_exit(1);


		}

		close(pipe_fd[0][0]);
		close(pipe_fd[1][1]);

		char * buffer = malloc(BUFFER_SIZE);

		ssize_t bytes_read = read(pipe_fd[1][0], buffer, BUFFER_SIZE);
		close(pipe_fd[1][0]);

		if(!bytes_read) {
			perror("Fail");
			exit(1);
		}

		count[i] = atoi(buffer);

		free(buffer);

	}

	int media, maximo = 0, minimo = count[0];

	for(int i = 0; i < N_EXEC; i++){

		media += count[i];
		if(count[i] > maximo) maximo = count[i];
		else if(count[i] < minimo) minimo = count[i];

	}

	media = media / N_EXEC;

	char * message = malloc(BUFFER_SIZE);
	snprintf(message, BUFFER_SIZE, "memoria: %d %d %d\n", minimo, media, maximo);
	write(1, message, strlen(message));
	free(message);

	return 0;

}