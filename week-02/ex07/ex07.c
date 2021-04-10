#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_SIZE (sizeof(int) * 3)

#define QTD_PEOPLE (*(int*)(pBuffer + sizeof(int)))
#define COUNTER (*(int*)(pBuffer + 2 * sizeof(int)))
#define OPTIONS (*(int*)(pBuffer))

typedef struct {
    char nome[30];
    int idade;
    int altura;
} Pessoa;

Pessoa pessoas[10];

int main() {
    void *pBuffer;

    pBuffer = malloc(TOTAL_SIZE);
    QTD_PEOPLE = 0;

    if (pBuffer == NULL) return -1;

    printf("Deseja adicionar novas pessoas? 1. Sim 2. Não\n");
    scanf("%d", &OPTIONS);

    while (OPTIONS != 2) {
        QTD_PEOPLE++;

        printf("Inserir nome: ");
        scanf("%s", pessoas[QTD_PEOPLE - 1].nome);
        getchar();

        printf("Inserir idade: ");
        scanf("%d", &pessoas[QTD_PEOPLE - 1].idade);

        printf("Inserir altura: ");
        scanf("%d", &pessoas[QTD_PEOPLE - 1].altura);

        printf("Deseja adicionar novas pessoas? 1. Sim 2. Não\n");
        scanf("%d", &OPTIONS);
    }
    
    for (COUNTER = 0; COUNTER < QTD_PEOPLE; COUNTER++) {
        printf("\nPessoa nº %d:\n", COUNTER + 1);
        printf("Nome: %s \n", pessoas[COUNTER].nome);
        printf("Idade: %d\n", pessoas[COUNTER].idade); 
        printf("Altura: %d\n", pessoas[COUNTER].altura); 
    }

    if (pBuffer != NULL) free(pBuffer);

    return 0;
}

