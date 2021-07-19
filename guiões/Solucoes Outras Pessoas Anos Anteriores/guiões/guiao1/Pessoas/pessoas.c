#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

//para o fstat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//para o isdigit
#include <ctype.h>

#include "pessoas.h"

int acrescentaPessoa(const char * nome, int idade) {
    printf("//////////Insert mode//////////\n");
    //int fd = open("pessoas_file", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    //int fd = open("pessoas_file", O_WRONLY | O_CREAT, 0600);
    int fd = open("pessoas_file", O_WRONLY | O_CREAT | O_APPEND, 0600);

    if(fd == -1) {
        printf("ERROR - Couldn't open or create registry file.\n");
        return 1;
    }
    
    PESSOA p;
    p.idade = idade;
    strcpy(p.nome,nome);

    //lseek(fd,(off_t) 0,SEEK_END); //-- o modo O_APPEND já faz isto sozinho
    if (write(fd,&p,sizeof(PESSOA)) < 1) {
        printf("ERROR - Couldn't write to registry file.\n");
        close(fd);
        return 1;
    }

    //This little section gets the file size, and then divides it by the struct size, to get the number of people in the registry, aka, the index of the most recent entry.
/*  struct stat st;
    fstat(fd, &st);
    off_t filesize = st.st_size;
    int pos = (int)filesize / sizeof(PESSOA); */

    int seek_res = lseek(fd, 0, SEEK_CUR); //faz a mesma coisa do comentário anterior
    int pos = seek_res / sizeof(PESSOA); 

    printf("Insertion succccessful - registo %d\n\n", pos);

    close(fd);
    return 0;
}

int pessoasIguais (PESSOA p1, PESSOA p2) {
    return (strcmp(p1.nome, p2.nome) == 0);
}

int atualizaIdade(const char *nome, int idade) {
    printf("/////////Update mode//////////\n");
    int fd = open("pessoas_file", O_RDWR, 0600);

    if(fd == -1) {
        printf("ERROR - Couldn't open registry file.\n");
        return 1;
    }

    else {
        //Esta zona é para o ex7, poder escrever com base num registo
        int registry = -1;
        int i = 1;

        if(isdigit(*nome))
            registry = atoi(nome); 
        ////////////////////////////////////////////////////////////

        PESSOA p1, p2;
        strcpy(p1.nome,nome);
        p1.idade = idade;

        int res = 0;
        while ((res = read(fd,&p2,sizeof(PESSOA)) > 0) && (!pessoasIguais(p1,p2)) && registry != i) {
            i++;
        }

        if (res > 0) {
            p2.idade = idade;
            lseek(fd, (off_t) -(sizeof(PESSOA)),SEEK_CUR); 
            if (write(fd,&p2,sizeof(PESSOA)) < 1) {
                printf("ERROR - Couldn't write to registry file.\n");
                close(fd);
                return 1;
            } 
            printf("Update successful\n\n");
            
        }

        else printf("ERROR - Registry entry not found\n");

        close(fd);

        return 0;
    }
}

void imprimePessoas () {
    int fd = open("pessoas_file", O_RDONLY);
    PESSOA p;

    while (read(fd,&p,sizeof(PESSOA)) > 0) {
        printf("%s - %d\n", p.nome, p.idade);
    }
    close (fd);
}
