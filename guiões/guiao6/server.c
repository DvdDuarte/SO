#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


int isRunning = 1;

void ctrl_c_handler(int signum) {
	isRunning = 0;
}

int main() {

	if(signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
        	puts("Erro com SIGINT");
        	exit(1);
        }
        
	printf("Starting server...\n");
	mkfifo("pip",0644);
	printf("Opening pipe...\n");
	int input_fd = open("pip", O_RDONLY);

	printf("opening log\n");
	int log_fd = open("log.txt", O_CREAT | O_WRONLY, 0644);

	printf("Reading\n");

	while(isRunning) {
		char buf[1024];
		int n = read(input_fd, buf, 1024);
		if(n > 0) {
			write(log_fd, buf, n);
			write(log_fd, "\n", 1);
		}
	}
	
	int fifo_value = unlink("pip");
	

	return 0;
}
