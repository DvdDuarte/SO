#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
	int pipe_fd[2];
	if(pipe(pipe_fd) < 0) {
		perror("pipe");
		exit(1);
	}

	int pid = -1;

	if((pid = fork()) == 0) {
		
		close(pipe_fd[1]);

		char buf[10];

		int bytes = read(pipe_fd[0], buf, 10);
		close(pipe_fd[0]);
		write(1, buf, bytes);
		_exit(0);
	} else {
		close(pipe_fd[0]);

		char *str = "Testar\n";

		write(pipe_fd[1], str, strlen(str));
		close(pipe_fd[1]);
		wait(NULL);
	}

	return 0;
}