#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

bool main(char* cidadao) { //vacinado

	int pids[9];

	for(int i = 0; i < 9; i++){
		if((pids[i] = fork() == 0)) {
			char file[9];
			sprintf(file,"regiao_%d",i);
			execlp("grep", "grep", file, cidadao, NULL);

		}
	} 

	int status;
	bool b = false;

	while(wait(&status) != -1)
		if(WIFEXITED(status)) 
			if(WEXITSTATUS(status)){
				b = true;
				for(int i = 0; i < 9; i++) 
					kill(pids[i], SIGKILL);
			}
		
	return b;

}