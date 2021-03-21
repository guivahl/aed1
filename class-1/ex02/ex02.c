#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main () {
    char *str, *strAux, c;
    int options, sizeStr = 0, sizeSplit = 0, i;

    do {
        printf("1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n");
        scanf("%d", &options);
        getchar();

        switch(options) {
            case 1: {
                if (sizeStr != 0) {
                    str[sizeStr] = '\n';
                    sizeStr++;
                    str = (char *) realloc(str, (sizeStr + 1) * sizeof(char));
                }
                while ((c = getchar()) != '\n') {
                    if(sizeStr == 0) str = (char *) malloc(2 + sizeof(char));
                    else str = (char *) realloc(str, (sizeStr + 2) * sizeof(char));

                    str[sizeStr] = c;
                    sizeStr++;
                }
                str[sizeStr] = '\0';
                break;
            }
            case 2: {
               sizeSplit = sizeStr - 1;

               while (sizeSplit > 0 && str[sizeSplit] != '\n') sizeSplit--;

               if (sizeSplit <= 0) {
                   if (str != NULL ) free(str);
                   sizeStr = 0;
                   break;
               }

               if (str[sizeSplit] == '\n') {
                   strAux = (char *) malloc((sizeSplit + 1) * sizeof(char));

                   for (i = 0; i < sizeSplit; i++) strAux[i] = str[i];

                   free(str);

                   strAux[sizeSplit] = '\0';
                   str = strAux;
                   sizeStr = sizeSplit;
               }
               break;
            }
            case 3: {
                if (sizeStr > 0) {
                    printf("%s", str);
                }
                else printf("Não existem nomes salvos!");

                printf("\n");
                
                break;
            }
            case 4: {
                if (sizeStr > 0) free(str);
            }
            default:
                break;
        }

    } while(options != 4);

}
