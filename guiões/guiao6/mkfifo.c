#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
	if(mkfifo("fifo",0644) == -1) 
		perror("Mkfifo Error");

	return 0;
}