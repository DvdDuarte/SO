#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char* argv[]) {
    int res = 0;

    int input_fd = open("/etc/passwd", O_RDONLY);
    int output_fd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int error_fd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    res = dup2(input_fd, 0);
    res = dup2(output_fd, 1);
    res = dup2(error_fd, 2);

    close(input_fd);
    close(output_fd);
    close(error_fd);

    setbuf(stdout,NULL); //prejudica em temos de desempenho (usar fflush é melhor)

    int read_res;
    char buffer;
    char line[1024];
    int i = 0;
    while((read_res = read(0, &buffer, 1)) != 0) {
        line[i] = buffer;
        i++;
        if(buffer == '\n') {
            write(1, line, i);
            write(2, line, i);

            printf("Hello world...\n");
            //nfflush(stdout);

            i = 0;
        }
    }

    return 0;
}