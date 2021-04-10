#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    int idade;
    int altura;
} Pessoa;

int main () {
    int opcoes = 0, qtdPessoas = 0;
    Pessoa *pessoas = NULL;

    printf("Deseja adicionar novas pessoas? 1. Sim 2. Não\n");
    scanf("%d", &opcoes);

    while (opcoes != 2) {

        qtdPessoas++;

        if (qtdPessoas == 0) {
            pessoas = (Pessoa *) malloc(sizeof(Pessoa));

            if (pessoas == NULL) return -1;
        }
        else {
            pessoas = (Pessoa *) realloc(pessoas, sizeof(Pessoa) * qtdPessoas);

            if (pessoas == NULL) return -1;
        }

        printf("Inserir nome: ");
        scanf("%s", pessoas[qtdPessoas - 1].nome);
        getchar();

        printf("Inserir idade: ");
        scanf("%d", &pessoas[qtdPessoas - 1].idade);

        printf("Inserir altura: ");
        scanf("%d", &pessoas[qtdPessoas - 1].altura);

        printf("Deseja adicionar novas pessoas? 1. Sim 2. Não\n");
        scanf("%d", &opcoes);
    }
    
    for (int i = 0; i < qtdPessoas; i++) {
        printf("\nPessoa nº %d:\n",  i + 1);
        printf("Nome: %s \n", pessoas[i].nome);
        printf("Idade: %d\n", pessoas[i].idade); 
        printf("Altura: %d\n", pessoas[i].altura); 
    }

    if (pessoas != NULL) free(pessoas);

    return 0;
}