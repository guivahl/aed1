#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char *string, *stringAuxiliary, charRead;
    int options, stringSize = 0, iterator, stringRemoveSize, stringIterator, removeStringIterator, subStringSizeCounter, hasMoreStrings;

    do {
        printf("1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n");
        scanf("%d", &options);
        getchar();

        switch(options) {
            case 1: {
                if (stringSize != 0) {
                    string[stringSize] = '\n';
                    stringSize++;
                    string = (char *) realloc(string, (stringSize + 1) * sizeof(char));
                    
                    if (string == NULL) return -1;
                }
                while ((charRead = getchar()) != '\n') {
                    if(stringSize == 0) string = (char *) malloc(2 + sizeof(char));
                    else string = (char *) realloc(string, (stringSize + 2) * sizeof(char));

                    if (string == NULL) return -1;

                    string[stringSize] = charRead;
                    stringSize++;
                }
                string[stringSize] = '\0';
                break;
            }
            case 2:  {
                stringIterator = 0;
                stringRemoveSize = 0;
                subStringSizeCounter = 0;

                if (stringSize <= 0) {
                    printf("Não existem nomes salvos!\n");
                    break;
                }

                while ((charRead = getchar()) != '\n') {
                    if(stringRemoveSize == 0) stringAuxiliary = (char *) malloc(2 + sizeof(char));
                    else stringAuxiliary = (char *) realloc(stringAuxiliary, (stringRemoveSize + 2) * sizeof(char));

                    if (stringAuxiliary == NULL) return -1;

                    stringAuxiliary[stringRemoveSize] = charRead;
                    stringRemoveSize++;
                }

                stringAuxiliary[stringRemoveSize] = '\0';

                while (string != NULL && stringSize > stringIterator && string[stringIterator] != '\0') {
                    while (string[stringIterator + subStringSizeCounter] != '\n' && string[stringIterator + subStringSizeCounter] != '\0') subStringSizeCounter++;

                    if (subStringSizeCounter == stringRemoveSize) {
                        iterator = 0;
                        while (string[stringIterator + iterator] == stringAuxiliary[iterator] && iterator < subStringSizeCounter) {
                            iterator++;
                        }
                        if (subStringSizeCounter == iterator) {
                            if (subStringSizeCounter == stringSize) {
                                free(string);
                                stringSize = 0;
                            } 
                            else {
                                removeStringIterator = stringIterator;
                                hasMoreStrings = 0;

                                if (string[removeStringIterator + subStringSizeCounter] == '\n') {
                                    hasMoreStrings = 1;
                                }                            

                                if (string[removeStringIterator + subStringSizeCounter] != '\0')
                                    while ((removeStringIterator + subStringSizeCounter + hasMoreStrings) <= stringSize) {
                                        string[removeStringIterator] = string[removeStringIterator + subStringSizeCounter + hasMoreStrings];
                                        removeStringIterator++;
                                    }

                                stringSize = stringSize - subStringSizeCounter - 1;

                                string = (char *) realloc(string, (stringSize + 2) * sizeof(char));

                                string[stringSize] = '\0';

                                subStringSizeCounter = 0;
                            }
                        }
                    }
                stringIterator+= subStringSizeCounter;

                if (stringSize > 0 && stringSize > (stringIterator + subStringSizeCounter) && string[stringIterator + subStringSizeCounter] == '\n') {
                    stringIterator+= 1;
                }                            

                subStringSizeCounter = 0;
                hasMoreStrings = 0;
                }
                if (stringAuxiliary != NULL) free(stringAuxiliary);
                break;
            }
            case 3: {
                if (stringSize > 0) {
                    printf("%s", string);
                }
                else printf("Não existem nomes salvos!");

                printf("\n");
                
                break;
            }
            case 4: {
                if (stringSize > 0) free(string);
            }
            default:
                break;
        }

    } while(options != 4);
      
    return 0;
}
