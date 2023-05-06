#include <stdio.h>

void merge(int array[], int left[], int leftSize, int right[], int rightSize) { // Recebe como par�metros um vetor (array), duas metades (left e right) e seus tamanhos (leftSize e rightSize)
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) { // � executado enquanto i � menor que o tamanho da metade esquerda e j � menor que o tamanho da metade direita.
        /**
         O objetivo do mergesort � combinar posteriormente os dois sub-vetores, esquerda e direita,
         ent�o ele compara se o elemento da posi��o i do vetor esquerda � menor do que o da posi��o j do vetor direita
        */
        if (left[i] <= right[j]) {
            array[k] = left[i]; // Ent�o, se for menor, o elemento do vetor da esquerda � adicionado a pr�xima posi��o
            i++;
        } else {
            array[k] = right[j]; // Se n�o, o elemento do vetor da direita � adicionado a pr�xima posi��o
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
    int left[mid]; // A divis�o gera o vetor da esquerda
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

    int array[narraysize]; // Declara o vetor com o �ndice do tamanho, aonde o usu�rio preenche o vetor
    printf("Digite os elementos do vetor: ");
    for (int i = 0; i < narraysize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    mergeSort(array, narraysize); // chama o m�todo de ordena��o

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
