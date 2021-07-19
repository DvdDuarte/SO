#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char const *argv[]) {
	char * fifo = strdup(argv[1]);
	int fd = open("fifo", O_RDONLY);
	char buffer[1024];
	int bytes = 0;

	while((bytes = read(fd, buffer, 1024)) > 0)
		write(1, buffer, bytes);

	close(fd);

	return 0;
}