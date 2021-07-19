#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main(char* regiao, int idade) { //vacinados

	int n = 0;

	char idade_string[6];
	sprintf(idade_string, " %d ", idade); //cc idade ...

	int pipe_fd1[2];

	if(pipe(pipe_fd1) == -1) {
		perror("Pipe creation failed!");
	}

	if(fork() == 0) {
		close(pipe_fd1[0]);
		dup2(pipe_fd1[1], 1);
		close(pipe_fd1[1]);
		execlp("grep", "grep", idade_string, regiao, NULL);
		_exit(1);
	}

	int pipe_fd2[2];
	
	if(pipe(pipe_fd2) == -1) {
		perror("Pipe creation failed!");
	}

	if(fork() == 0) {
		close(pipe_fd2[0]);
		dup2(pipe_fd1[0], 0);
		close(pipe_fd1[0]);
		dup2(pipe_fd2[1], 1);
		close(pipe_fd2[1]);
		execlp("wc", "wc", "-l", NULL);
		_exit(1);
	}

	close(pipe_fd1[0]);
	close(pipe_fd2[1]);

	int bytes_read = 0;
	char buf[1025];
	bytes_read = read(pipe_fd2[0], buf, 1024);
	close(pipe_fd2[0]);
	buf[bytes_read] = 0;
	return atoi(buf);

}