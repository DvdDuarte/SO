#ifndef _PESSOAS
#define _PESSOAS

typedef struct pessoa {
    char nome[100];
    int idade;
} PESSOA;

//retornam 1 caso seja feito com sucesso
int acrescentaPessoa(const char * nome, int idade);
int atualizaIdade(const char *nome, int idade);
int pessoasIguais (PESSOA p1, PESSOA p2);
void imprimePessoas ();

#endif