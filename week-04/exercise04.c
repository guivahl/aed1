#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DEFAULT_LEFT_SIZE 0

#define INSERTION_SORT 1
#define SELECTION_SORT 2
#define QUICK_SORT 3
#define MERGE_SORT 4

void insertionSort(int *values, int size)
{
    int minimum, minimumIndex, auxiliary, iterator, secondIterator;

    for (int iterator = 1; iterator < size; iterator++)
    {
        for (int secondIterator = iterator; 
            secondIterator > 0 && values[secondIterator] < values[secondIterator-1] && secondIterator < size; 
            secondIterator--)
        {
            auxiliary = values[secondIterator];
            values[secondIterator] = values[secondIterator - 1];
            values[secondIterator - 1] = auxiliary;
        }
    }
}

void selectionSort(int *values, int size)  {    
    int iterator, secondIterator, minimum, minimumIndex, auxiliary;
    
    for (iterator = 0; iterator < size - 1; iterator++)
    {
        minimum = values[iterator];

        for (secondIterator = iterator + 1; secondIterator < size; secondIterator++)
        {
            if (values[secondIterator] < minimum)
            {
                minimum = values[secondIterator];
                minimumIndex = secondIterator;
            }
        }

        auxiliary = values[iterator];
        values[iterator] = values[minimumIndex];
        values[minimumIndex] = auxiliary;

        minimumIndex = iterator + 1;
    }
};

void quickSort(int *values, int left, int right)
{
    int medium, auxiliary, iterator, secondIterator, step;

    iterator = left;
    secondIterator = right;

    step = (left + right) / 2;

    medium = values[step];

    do
    {
        while (values[iterator] < medium)
            iterator++;

        while (medium < values[secondIterator])
            secondIterator--;

        if (iterator <= secondIterator)
        {
            auxiliary = values[iterator];
            values[iterator] = values[secondIterator];
            values[secondIterator] = auxiliary;
            iterator++;
            secondIterator--;
        }
    } while (iterator <= secondIterator);

    if (left < secondIterator)
        quickSort(values, left, secondIterator);
    if (iterator < right)
        quickSort(values, iterator, right);
}

void mergeSort(int *values, int left, int right)
{
    int middle = (left + right) / 2;
    int iterator = 0, startAuxiliary = 0, middleAuxiliary = 0, totalSize = 0;

    middleAuxiliary = middle + 1;
    startAuxiliary = left;
    totalSize = right - left + 1;

    int auxArray[totalSize];

    if (left < right)
    {
        mergeSort(values, left, middle);
        mergeSort(values, middleAuxiliary, right);

        while (startAuxiliary <= middle && middleAuxiliary <= right)
        {
            if (values[startAuxiliary] < values[middleAuxiliary])
            {
                auxArray[iterator] = values[startAuxiliary];
                startAuxiliary++;
            }
            else
            {
                auxArray[iterator] = values[middleAuxiliary];
                middleAuxiliary++;
            }
            iterator++;
        }

        while (startAuxiliary <= middle)
        {
            auxArray[iterator] = values[startAuxiliary];
            iterator++;
            startAuxiliary++;
        }

        while (middleAuxiliary <= right)
        {
            auxArray[iterator] = values[middleAuxiliary];
            iterator++;
            middleAuxiliary++;
        }

        for (iterator = left; iterator <= right; iterator++)
        {
            values[iterator] = auxArray[iterator - left];
        }
    }
};

void populate(int *values, int size)
{
    int iterator;

    srand(time(NULL));

    for (int iterator = 0; iterator < size; iterator++)
    {
        values[iterator] = rand() % 100000;
    }
}

void list(int *values, int size)
{
    for (int iterator = 0; iterator < size; iterator++)
    {
        printf("%d ", values[iterator]);
    }
    printf("\n");
}

void checkIfArrayIsOrdened (int *values, int size) {
    int iterator;

    printf("Checando se array está ordenado...\n");

    for (iterator = 0; iterator < size; iterator++)
        if (values[iterator] > values[iterator + 1]){
            printf("Não está ordenado.\n\n");
            return;
        }
            
    printf("Está ordenado.\n\n");
}

int main()
{
    struct timeval end, start;
    int size = 0, options = 0, *values = NULL;

    printf("Digite o tamanho do vetor.\n");
    scanf("%d", &size);

    values = (int *)malloc(size * sizeof(int));

    populate(values, size);

    printf("\nArray criado: ");
    list(values, size);

    printf("Insira o número referente ao método de sort escolhido:\n1) Insertion Sort\n2) Selection Sort\n3) Quick Sort\n4) Merge Sort\n5) Sair\n");
    scanf("%d", &options);

    gettimeofday(&start, NULL);

    switch(options) {
        case INSERTION_SORT: {
            insertionSort(values, size);
            break;
        }        
        case SELECTION_SORT: {
            selectionSort(values, (size - 1));
            break;
        }
        case QUICK_SORT: {
            quickSort(values, DEFAULT_LEFT_SIZE, (size - 1));
            break;
        }
        case MERGE_SORT: {
            mergeSort(values, DEFAULT_LEFT_SIZE, (size - 1));
            break;
        }
        default: break;
    }

    gettimeofday(&end, NULL);

    printf("\nO algoritmo escolhido demorou %lu microssegundos para ser executado!\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    printf("\nArray depois do algoritmo de ordenação: ");
    list(values, size);

    checkIfArrayIsOrdened(values, (size - 1));

    free(values);

    return 0;
}
