#include <stdio.h>

// Implementação do algoritmo ShellSort
void shellSort(int array[], int narraysize) { // Recebe como parâmetro o vetor e seu tamanho
    int i, j, gap, temp; // Gap é o intervalo usado pelo algoritmo Shellsort, temp é uma variável auxiliar
    for (gap = narraysize/2; gap > 0; gap /= 2) { // Divide o "problema" em 2 a cada iteração
        for (i = gap; i < narraysize; i++) { // Loop interno do Shellsort, começa no intervalo da divisão (gap) e continua até atingir o tamanho do array
            temp = array[i]; // Armazena o valor atual do array numa variável temporária para ajustar sua posição
            /**
            Verifica se o elemento anterior é maior do que o valor armazenado em temp.
            Variável j é inicializada em i, que é a posição atual do elemento avaliado.
            Enquanto j for menor que o intervalo (gap), e e o valor anterior (arr[j-gap]) é maior do que o valor armazenado em temp, o loop continuará.
            */
            for (j = i; j >= gap && array[j-gap] > temp; j -= gap)
                array[j] = array[j-gap]; // Se for, move o elemento anterior para a posição desse elemento
            array[j] = temp; // Move o valor armazenado em temp para a posição correta no array.
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
