#include <stdio.h>

// Implementação do algoritmo QuickSort
void QuickSort(int array[], int left, int right) { // Recebe como parâmetro um vetor, o índice inicial left, e o final right.
    int i = left; // i e j percorrerão o vetor a partir dos índices
    int j = right;
    int temp; // variável que armazenará o valor temporariamente durante as trocas
    int pivot = array[(left + right) / 2]; // divide o vetor em um valor pivô, pega-se as extremidades e divide por 2

/**
À medida que o loop é executado, o índice "i" é incrementado para a direita e o índice "j" é decrementado para a esquerda,
até que os dois índices se encontrem, isto é, não há mais trocas a serem feitas.
*/
    while (i <= j) { //Enquanto
        while (array[i] < pivot) { // Procura pelo primeiro elemento à esquerda do array que é maior ou igual ao pivô
            i++;
        }
        while (array[j] > pivot) { // Procura pelo primeiro elemento à direita do array que é menor ou igual ao pivô
            j--;
        }
        if (i <= j) { // Verifica se o valor de i está a direita de j
            temp = array[i]; // Troca os elementos de posição
            array[i] = array[j];
            array[j] = temp;
            i++; // Atualiza os índices de i e j para continuar a busca
            j--;
        }
    }
// Esses blocos chamam a função QuickSort() recursivamente para classificar as porções à esquerda e à direita do pivô.
    if (left < j) { // Comparação entre o índice do primeiro elemento do vetor e o índice final do vetorzinho à direita do pivô
        QuickSort(array, left, j);
    }
    if (i < right) { // Comparação entre o índice final do vetorzinho à esquerda do pivô e o o índice final do vetor
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
