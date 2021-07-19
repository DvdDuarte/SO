#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE 1024

char **parse_entry(char** position); //Já existe

int main() {

	printf("Starting server...");
	mkfifo("server",0644);
	int fd_leitura = open("server",O_RDONLY);
	open("server",O_WRONLY);

	int fds[9];

	for(int i = 0; i < 9; i++) {
		char nome_ficheiro[7];
		sprintf(nome_ficheiro,"zona_%d",i);
		fds[i] = open(nome_ficheiro, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

	char buffer[1024];
	int bytes_read = 0;

	while(read(fd_leitura,buffer,BUF_SIZE) > 0) {
		char *save_buf = buffer;
		char **fields; // 0 - cc 1 - idade 2 - regiao
		while(fields = parse_entry(&save_buf)){
			char line[strlen(fields[0]) + strlen(fields[1]) + strlen(fields[2]) + 3]; // Tamanho cc + Tamanho idade + Tamanho regiao + 3  "cc idade regiao"
			int to_write = sprintf(line, "%s %s %s", fields[0], fields[1], fields[2]);  // Devolve o nmr de caracteres guardados no array de char

			write(fds[atoi(fields[2])], line, to_write);
		}
	}

	return 0;
}