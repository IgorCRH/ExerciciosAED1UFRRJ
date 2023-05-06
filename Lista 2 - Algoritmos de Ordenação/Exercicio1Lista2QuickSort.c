#include <stdio.h>

// Implementação do algoritmo QuickSort
void QuickSort(int array[], int left, int right) { //
    int i = left;
    int j = right;
    int temp;
    int pivot = array[(left + right) / 2];

    while (i <= j) {
        while (array[i] < pivot) {
            i++;
        }
        while (array[j] > pivot) {
            j--;
        }
        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        QuickSort(array, left, j);
    }
    if (i < right) {
        QuickSort(array, i, right);
    }
}


int main() {
    int array[] = {4, 67, 5, 34, 21, 32, 60, 1, 13, 53, 11, 90, 3, 17}; // Elementos do vetor da lista
    int narraysize = sizeof(array)/sizeof(array[0]); // Calcula o tamanho do vetor

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++)
        printf("%d ", array[i]);

    QuickSort(array, 0,narraysize-1);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++)
        printf("%d ", array[i]);

    return 0;
}
