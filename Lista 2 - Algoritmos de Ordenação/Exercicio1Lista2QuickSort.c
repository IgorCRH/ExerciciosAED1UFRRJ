#include <stdio.h>

// Implementa��o do algoritmo QuickSort
void QuickSort(int array[], int left, int right) { // Recebe como par�metro um vetor, o �ndice inicial left, e o final right.
    int i = left; // i e j percorrer�o o vetor a partir dos �ndices
    int j = right;
    int temp; // vari�vel que armazenar� o valor temporariamente durante as trocas
    int pivot = array[(left + right) / 2]; // divide o vetor em um valor piv�, pega-se as extremidades e divide por 2

/**
� medida que o loop � executado, o �ndice "i" � incrementado para a direita e o �ndice "j" � decrementado para a esquerda,
at� que os dois �ndices se encontrem, isto �, n�o h� mais trocas a serem feitas.
*/
    while (i <= j) { //Enquanto
        while (array[i] < pivot) { // Procura pelo primeiro elemento � esquerda do array que � maior ou igual ao piv�
            i++;
        }
        while (array[j] > pivot) { // Procura pelo primeiro elemento � direita do array que � menor ou igual ao piv�
            j--;
        }
        if (i <= j) { // Verifica se o valor de i est� a direita de j
            temp = array[i]; // Troca os elementos de posi��o
            array[i] = array[j];
            array[j] = temp;
            i++; // Atualiza os �ndices de i e j para continuar a busca
            j--;
        }
    }
// Esses blocos chamam a fun��o QuickSort() recursivamente para classificar as por��es � esquerda e � direita do piv�.
    if (left < j) { // Compara��o entre o �ndice do primeiro elemento do vetor e o �ndice final do vetorzinho � direita do piv�
        QuickSort(array, left, j);
    }
    if (i < right) { // Compara��o entre o �ndice final do vetorzinho � esquerda do piv� e o o �ndice final do vetor
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
