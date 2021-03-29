#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_PEOPLE_POSITION (1 * sizeof(int))

#define NAME_SIZE (10 * sizeof(char))
#define AGE_SIZE (1 * sizeof(int))
#define PHONE_SIZE (11 * sizeof(char))

#define TOTAL_SIZE ((10 * sizeof(char)) + (1 * sizeof(int)) + (11 * sizeof(char)))

int main () {
    int options = 0, qtdPeople = 0;
    void *pBuffer = NULL;

    printf("Agenda\nRegras:\n1- Nome até caracteres\n2- Telefones DDD+Número\n");

    pBuffer = malloc(QTD_PEOPLE_POSITION);

    *(int*)(pBuffer) = 0;

    do {
        printf("1) Incluir\n2) Apagar\n3) Buscar\n4) Listar\n5) Sair\n");
        scanf("%d", &options);
        getchar();

        switch(options) {
            case 1: {
                pBuffer = realloc(pBuffer, (QTD_PEOPLE_POSITION) + (TOTAL_SIZE * (qtdPeople + 1)));

                printf("Inserir nome: ");
                scanf("%s", (char*)(pBuffer + QTD_PEOPLE_POSITION + (TOTAL_SIZE * qtdPeople)));
                getchar();
        
                printf("Inserir idade: ");
                scanf("%d", (int*)(pBuffer + QTD_PEOPLE_POSITION + NAME_SIZE + (TOTAL_SIZE * qtdPeople)));
        
                printf("Inserir telefone: ");
                scanf("%s", (char*)(pBuffer + QTD_PEOPLE_POSITION + NAME_SIZE + AGE_SIZE + (TOTAL_SIZE * qtdPeople)));
                
                qtdPeople = qtdPeople + 1;  

                *(int*)(pBuffer) = qtdPeople;

                break;
            }
            case 2:{
            }
            case 3: {
            }
            case 4: {
                for(int i = 0; i < qtdPeople; i++) {
                    printf("Nome: %s \n", (char*)(pBuffer + QTD_PEOPLE_POSITION + (TOTAL_SIZE * i)));
                    printf("Idade: %d\n", *(int*)(pBuffer + QTD_PEOPLE_POSITION + NAME_SIZE + (TOTAL_SIZE * i))); 
                    printf("Telefone: %s\n", (char*)(pBuffer + QTD_PEOPLE_POSITION + NAME_SIZE + AGE_SIZE + (TOTAL_SIZE * i))); 
                }
                break;
            }            
            case 5: {
                if(pBuffer = NULL) free(pBuffer);
            }
            default:
                break;
        }

    } while(options != 5);
      
    return 0;
}
