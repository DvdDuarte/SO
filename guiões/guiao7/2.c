#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h> 


int main(int argc, char *argv[]) {

	int filhos = argc - 2;
	char **args = argv;
	int res, status;
	int pids[filhos];
	int pid;

	 for(int i = 0; i < filhos; i++) {
	 	pid = fork();

	 	switch(pid){
	 		case -1:
	 			perror("Fork not created.\n");
	 			return -1;
	 			break;

	 		case 0:
	 			pids[i] = getpid();

	 			if((res = execlp("grep", "grep", args[1], args[i + 2], NULL)) < 0) 
	 				perror("Couln't execute command.\n");
	 			_exit(res);
	 			break;

	 		default:
	 			printf("Child %d is executing grep %s %s\n", pid, args[1], args[i + 2]);


	 	}
	 }

	 int found = 0;
	 pid_t terminated_pid;

	 for(int i = 0; i < filhos && !found; i++) {
	 	terminated_pid = wait(&status);

	 	if(WIFEXITED(status)) {
			if(WEXITSTATUS(status) == 0) { 
	 			printf("Father - process %d ended. Found the word.\n", terminated_pid);
	 			found = 1;
	 		}

	 		else printf("Father - process %d ended. Word not found.\n", terminated_pid);
	 	}
	 }
	 	if(found) {
	 		for(int f = 0; f < filhos - 1; f++) 
	 			if(pids[f] != terminated_pid && pids[f] > 0)
	 				res = kill(pids[f],SIGKILL);	 		
	 	}

	return 0;
}