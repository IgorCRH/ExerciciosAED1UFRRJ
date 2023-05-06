#include <stdio.h>

// Implementa��o do algoritmo ShellSort
void shellSort(int array[], int narraysize) { // Recebe como par�metro o vetor e seu tamanho
    int i, j, gap, temp; // Gap � o intervalo usado pelo algoritmo Shellsort, temp � uma vari�vel auxiliar
    for (gap = narraysize/2; gap > 0; gap /= 2) { // Divide o "problema" em 2 a cada itera��o
        for (i = gap; i < narraysize; i++) { // Loop interno do Shellsort, come�a no intervalo da divis�o (gap) e continua at� atingir o tamanho do array
            temp = array[i]; // Armazena o valor atual do array numa vari�vel tempor�ria para ajustar sua posi��o
            /**
            Verifica se o elemento anterior � maior do que o valor armazenado em temp.
            Vari�vel j � inicializada em i, que � a posi��o atual do elemento avaliado.
            Enquanto j for menor que o intervalo (gap), e e o valor anterior (arr[j-gap]) � maior do que o valor armazenado em temp, o loop continuar�.
            */
            for (j = i; j >= gap && array[j-gap] > temp; j -= gap)
                array[j] = array[j-gap]; // Se for, move o elemento anterior para a posi��o desse elemento
            array[j] = temp; // Move o valor armazenado em temp para a posi��o correta no array.
        }
    }
}

int main() {
    int array[] = {4, 67, 5, 34, 21, 32, 60, 1, 13, 53, 11, 90, 3, 17}; // Elementos do vetor da lista
    int narraysize = sizeof(array)/sizeof(array[0]); // Calcula o tamanho do vetor

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++)
        printf("%d ", array[i]);

    shellSort(array, narraysize);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++)
        printf("%d ", array[i]);

    return 0;
}
