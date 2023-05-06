#include <stdio.h>

void merge(int array[], int left[], int leftSize, int right[], int rightSize) { // Recebe como parâmetros um vetor (array), duas metades (left e right) e seus tamanhos (leftSize e rightSize)
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) { // É executado enquanto i é menor que o tamanho da metade esquerda e j é menor que o tamanho da metade direita.
        /**
         O objetivo do mergesort é combinar posteriormente os dois sub-vetores, esquerda e direita,
         então ele compara se o elemento da posição i do vetor esquerda é menor do que o da posição j do vetor direita
        */
        if (left[i] <= right[j]) {
            array[k] = left[i]; // Então, se for menor, o elemento do vetor da esquerda é adicionado a próxima posição
            i++;
        } else {
            array[k] = right[j]; // Se não, o elemento do vetor da direita é adicionado a próxima posição
            j++;
        }
        k++;
    }

    while (i < leftSize) { // Adiciona os elementos restantes da metade esquerda ao vetor array.
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) { // Adiciona os elementos restantes da metade direita ao vetor array.
        array[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int arraySize) {
    if (arraySize < 2) {
        return;
    }

    int mid = arraySize / 2; // Divide o vetor em dois
    int left[mid]; // A divisão gera o vetor da esquerda
    int right[arraySize - mid]; // E o vetor da direita

    for (int i = 0; i < mid; i++) { // Copia os elementos para a metade esquerda do vetor
        left[i] = array[i];
    }

    for (int i = mid; i < arraySize; i++) { // Copia os elementos para a metade direita do vetor
        right[i - mid] = array[i];
    }

    // Chamadas recursivas para dividir sucessivamente os vetores
    mergeSort(left, mid); // Divide o sub-vetor da esquerda em dois
    mergeSort(right, arraySize - mid); // Divide o sub-vetor da direita em dois
    merge(array, left, mid, right, arraySize - mid); // Recombina o vetor
}

int main() {
    int narraysize; // Tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &narraysize);

    int array[narraysize]; // Declara o vetor com o índice do tamanho, aonde o usuário preenche o vetor
    printf("Digite os elementos do vetor: ");
    for (int i = 0; i < narraysize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    mergeSort(array, narraysize); // chama o método de ordenação

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
