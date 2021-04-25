#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_VARIABLES (2 * sizeof(int))
#define NAME_SIZE (10 * sizeof(char))

#define OPTIONS (*(int*)(pBuffer))
#define SEARCH_NAME ((char*)(pBuffer + QTD_VARIABLES))

struct person{
    char name[10];
    int age;
    char phone[12];
} ;
typedef struct person Person;

struct nodo {
    Person person;
    struct nodo *pointerNext;
    struct nodo *pointerPrevious;
};
typedef struct nodo Nodo;
struct fila  {
    unsigned int count;
    Nodo *pointerFirst;
    Nodo *pointerLast;
};
typedef struct fila Fila;

void insert(Fila *fila) {
        fila->count++;

        Nodo *nodo = malloc(sizeof(Nodo));

        if (fila->pointerFirst == NULL) {
            nodo->pointerNext = NULL;
            nodo->pointerPrevious = NULL;
            fila->pointerFirst = nodo;
            fila->pointerLast = nodo;
        } else {
            fila->pointerLast->pointerNext = nodo;
            nodo->pointerPrevious = fila->pointerLast;
            fila->pointerLast = nodo;
        }

        printf("Inserir nome: ");
        scanf("%s", nodo->person.name);
        getchar();
        
        printf("Inserir idade: ");
        scanf("%d", &nodo->person.age);
        
        printf("Inserir telefone: ");
        scanf("%s", nodo->person.phone);
}

void search(Fila *fila, void *pBuffer) {        
        Nodo *nodo = malloc(sizeof(Nodo));

        scanf("%s",  (char*)(pBuffer + QTD_VARIABLES));
        getchar();

        printf("Nome: %s \n", (char*)(pBuffer + QTD_VARIABLES));

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            if(strcmp(nodo->person.name, (char*)(pBuffer + QTD_VARIABLES)) == 0) { 
                printf("Nome: %s \n", nodo->person.name);
                printf("Idade: %d\n", nodo->person.age); 
                printf("Telefone: %s\n", nodo->person.phone); 
            }
        }
}

void delete(Fila *fila, void *pBuffer) {        
        Nodo *nodo = malloc(sizeof(Nodo));

        scanf("%s",  (char*)(pBuffer + QTD_VARIABLES));
        getchar();

        printf("Nome: %s \n", (char*)(pBuffer + QTD_VARIABLES));

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            if(strcmp(nodo->person.name, (char*)(pBuffer + QTD_VARIABLES)) == 0) { 
                nodo->pointerNext->pointerPrevious = nodo->pointerPrevious;
                nodo->pointerPrevious->pointerNext = nodo->pointerNext;

                if (nodo->pointerNext == NULL) {
                    fila->pointerLast = nodo->pointerPrevious;
                }
                if (nodo->pointerPrevious == NULL) {
                    fila->pointerFirst = nodo->pointerNext;
                }
            }
        }

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            printf("Nome: %s \n", nodo->person.name);
            printf("Idade: %d\n", nodo->person.age); 
            printf("Telefone: %s\n", nodo->person.phone);      
        }

        free(nodo);
}

int main () {
    void *pBuffer = NULL;
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->count = 0;
    
    pBuffer = malloc(QTD_VARIABLES + NAME_SIZE);

    OPTIONS = 0;

    do {
        // printf("1) Incluir\n2) Apagar\n3) Buscar\n4) Listar\n5) Sair\n");
        scanf("%d", &OPTIONS);
        getchar();

        switch(OPTIONS) {
            case 1: {
                insert(fila);

                break;
            }
            case 2: {
                delete(fila, pBuffer);

                break;
            }
            case 3: {
                search(fila, pBuffer);

                break;
            }
    //         case 4: {
    //             for(int i = 0; i < qtdPeople; i++) {
    //                 printf("Nome: %s \n", (char*)(pBuffer + QTD_VARIABLES + (TOTAL_SIZE * i)));
    //                 printf("Idade: %d\n", *(int*)(pBuffer + QTD_VARIABLES + NAME_SIZE + (TOTAL_SIZE * i))); 
    //                 printf("Telefone: %s\n", (char*)(pBuffer + QTD_VARIABLES + NAME_SIZE + AGE_SIZE + (TOTAL_SIZE * i))); 
    //             }
    //             break;
    //         }            
    //         case 5: {
    //             if(pBuffer != NULL) free(pBuffer);
    //         }
            default:
                break;
        }

    } while(OPTIONS != 5);
      
    return 0;
}
