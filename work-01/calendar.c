#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define QTD_VARIABLES (5 * sizeof(int))
#define NAME_SIZE (10 * sizeof(char))

#define OPTIONS (*(int*)(pBuffer))
#define SORT_FIELD (*(int*)(pBuffer + sizeof(int)))
#define SORT_ORDER (*(int*)(pBuffer + 2 * sizeof(int)))
#define OFFSET (*(int*)(pBuffer + 3 * sizeof(int)))
#define SHOULD_SWAP (*(int*)(pBuffer + 4 * sizeof(int)))

#define SORT_NO 1
#define SORT_NAME 2
#define SORT_AGE 3
#define SORT_PHONE 4

#define ORDER_ASC 1 
#define ORDER_DESC 2

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

        Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));

        nodo->pointerNext = NULL;
        nodo->pointerPrevious = NULL;

        if (fila->pointerFirst == NULL) {
            fila->pointerFirst = nodo;
            fila->pointerLast = nodo;
        } else {
            nodo->pointerPrevious = fila->pointerLast;
            fila->pointerLast->pointerNext = nodo;
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

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            if(strcmp(nodo->person.name, (char*)(pBuffer + QTD_VARIABLES)) == 0) { 
                if (nodo->pointerPrevious != NULL) nodo->pointerPrevious->pointerNext = nodo->pointerNext;
                else {
                    fila->pointerFirst = nodo->pointerNext;
                }
                if (nodo->pointerNext != NULL)  nodo->pointerNext->pointerPrevious = nodo->pointerPrevious;
                else {
                    fila->pointerLast = nodo->pointerPrevious;
                }
                fila->count--;
            }
        }

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            printf("Nome: %s \n", nodo->person.name);
            printf("Idade: %d\n", nodo->person.age); 
            printf("Telefone: %s\n", nodo->person.phone);      
        }

        free(nodo);
}

void sort(Fila *fila, void *pBuffer) {      
        Nodo *nodo = malloc(sizeof(Nodo)); 

        OFFSET = 0;
        SHOULD_SWAP = 0;

        printf("Deseja ordenar a agenda? \n1) N??o\n2) Por nome\n3) Por idade\n4) Por telefone\n5) Sair\n");
        scanf("%d", &SORT_FIELD);
        getchar(); 

        if (SORT_FIELD != SORT_NO) { 
            printf("Como a agenda deve ser ordenada? \n1) Crescente\n2) Decrescente\n");
            scanf("%d", &SORT_ORDER);
            getchar();

            Nodo *auxNodo = malloc(sizeof(Nodo)); 
            Nodo *swapNodo = malloc(sizeof(Nodo)); 

            switch(SORT_FIELD) {
                case SORT_NAME:
                    OFFSET += offsetof(struct person, name);
                    break;
                case SORT_AGE:
                    OFFSET += offsetof(struct person, age);
                    break;
                case SORT_PHONE:
                    OFFSET += offsetof(struct person, phone);
                    break;
                default:
                break;
            }

            for (nodo = fila->pointerFirst; nodo->pointerNext != NULL;nodo = nodo->pointerNext) {
                for (auxNodo = nodo->pointerNext; auxNodo != NULL; auxNodo = auxNodo->pointerNext) {
                    if (SORT_NAME == SORT_FIELD || SORT_PHONE == SORT_FIELD ) {
                        if (SORT_ORDER == ORDER_ASC) {                        
                            if (strcmp((char *)((char *)auxNodo->pointerPrevious + OFFSET), (char *)((char *)auxNodo + OFFSET)) > 0) {
                                SHOULD_SWAP = 1;
                            }    
                        }  
                        if (SORT_ORDER == ORDER_DESC) {                       
                            if (strcmp((char *)((char *)auxNodo->pointerPrevious + OFFSET), (char *)((char *)auxNodo + OFFSET)) < 0) {
                                SHOULD_SWAP = 1;
                            }
                        }
                    }
                    if (SORT_AGE == SORT_FIELD) {     
                        if (SORT_ORDER == ORDER_ASC) {                   
                            if (*(int *)((char *)auxNodo->pointerPrevious + OFFSET) - *(int *)((char *)auxNodo + OFFSET) > 0) {
                                SHOULD_SWAP = 1;
                            }
                        }                           
                        if (SORT_ORDER == ORDER_DESC) {                   
                            if (*(int *)((char *)auxNodo->pointerPrevious + OFFSET) - *(int *)((char *)auxNodo + OFFSET) < 0) {
                                SHOULD_SWAP = 1;
                            }
                        }
                    }
                    
                    if (SHOULD_SWAP == 1) {
                        if(fila->pointerFirst == auxNodo->pointerPrevious) {
                            fila->pointerFirst = auxNodo;
                        }
                        if(fila->pointerLast == auxNodo){
                            fila->pointerLast = auxNodo->pointerPrevious;
                        } 

                        swapNodo->pointerNext = auxNodo->pointerPrevious;
                        swapNodo->pointerPrevious = auxNodo->pointerPrevious->pointerPrevious;

                        auxNodo->pointerPrevious->pointerNext = auxNodo->pointerNext; 
                        auxNodo->pointerPrevious->pointerPrevious = auxNodo;

                        auxNodo->pointerNext = swapNodo->pointerNext; 
                        auxNodo->pointerPrevious = swapNodo->pointerPrevious;

                        if (auxNodo->pointerNext->pointerNext != NULL) {
                            auxNodo->pointerNext->pointerNext->pointerPrevious = swapNodo->pointerNext;
                        }

                        auxNodo = swapNodo; 
                        nodo = fila->pointerFirst; 
                    }
                    
                    SHOULD_SWAP = 0;
                }
            }

            free(auxNodo);
            free(swapNodo);
        }

        for (nodo = fila->pointerFirst; nodo != NULL; nodo = nodo->pointerNext) {
            printf("\nNome: %s \n", nodo->person.name);
            printf("Idade: %d\n", nodo->person.age); 
            printf("Telefone: %s\n\n", nodo->person.phone); 
        }

        free(nodo);
}

int main () {
    void *pBuffer = NULL;
    Fila *fila = (Fila *) malloc(sizeof(Fila));
    fila->count = 0;
    fila->pointerFirst = NULL;
    fila->pointerLast = NULL;
    
    pBuffer = malloc(QTD_VARIABLES + NAME_SIZE);

    printf("Agenda\nRegras:\n1- Nome at?? 10 caracteres\n2- Telefones DDD+N??mero\n");

    do {
        OPTIONS = 0;

        printf("1) Incluir\n2) Apagar\n3) Buscar\n4) Listar/Ordenar\n5) Sair\n");
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
            case 4: {
                sort(fila, pBuffer);

                break;
            }
            case 5:
            default:
                break;
        }

    } while(OPTIONS != 5);

    if(fila != NULL) free(fila);
    if(pBuffer != NULL) free(pBuffer);
      
    return 0;
}
