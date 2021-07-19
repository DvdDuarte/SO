#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
	char buffer[1024];
	int bytes = 0;
	int fd = open("fifo", O_WRONLY);

	while((bytes = read(0, buffer, 1024)) > 0)
		write(fd, buffer, bytes);

	close(fd);

	return 0;
}