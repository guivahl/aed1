#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {
    char *str, *strAux, c;
    int options, sizeStr = 0, sizeSplit = 0;

    do {
        printf("1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n");
        scanf("%d", &options);
        getchar();

        switch(options) {
            case 1: {
                if (sizeStr != 0) {
                    str[sizeStr] = ',';
                    sizeStr++;
                    str = (char *) realloc(str, sizeStr * sizeof(char));
                }
                while ((c = getchar()) != '\n') {
                    if(sizeStr == 0) str = (char *) malloc(sizeof(char));
                    else str = (char *) realloc(str, sizeStr * sizeof(char));

                    str[sizeStr] = c;
                    sizeStr++;
                }
                break;
            }
            case 2: {
               sizeSplit = sizeStr--;

               while (sizeSplit > 0 && str[sizeSplit] != ',') sizeSplit--;

               if (sizeSplit == 0) {
                   free(str);
                   sizeStr = 0;
               }
               else if (str[sizeSplit] == ',') {
                   strAux = (char *) malloc(sizeSplit * sizeof(char));

                   for (int i = 0; i < sizeSplit; i++) strAux[i] = str[i];

                   free(str);

                   str = strAux;
                   sizeStr = sizeSplit;
               }
               break;
            }
            case 3: {
                if (sizeStr > 0) {
                   for (int i = 0; i < sizeStr; i++) {
                       if (str[i] == ',') printf("\n");
                       else printf("%c", str[i]);
                   }
                }
                else printf("Não existem nomes salvos!");

                printf("\n");
                
                break;
            }
            case 4:
            default:
                break;
        }

    } while(options != 4);

    free(str);
}
