  
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int agrc, char const *argv[]){
	for(int i = 0; i < 11; i++){
		if(!fork()){
			_exit(i);
		}
	}

	int exit_status;
	while(wait(&exit_status) != -1) {
		printf("Child %d\n", WEXITSTATUS(exit_status));
	}
	return 0;
}