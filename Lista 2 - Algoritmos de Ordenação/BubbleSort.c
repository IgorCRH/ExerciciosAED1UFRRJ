#include <stdio.h>

void bubbleSort(int array[], int arraySize) {
    for (int i = 0; i < arraySize - 1; i++) {
        // O loop externo controla a passagem atual no Bubble Sort. Cada passagem coloca o maior elemento no final.
        // Como o maior elemento é colocado na posição correta a cada passagem, o tamanho da parte não ordenada diminui em 1.

        for (int j = 0; j < arraySize - i - 1; j++) {
            // O loop interno percorre a parte não ordenada do vetor.
            // Como o maior elemento já está na posição correta após cada passagem, não é necessário comparar com os elementos já ordenados.
            // A cada iteração, compara-se o elemento atual com o próximo elemento e realiza a troca se necessário.

            if (array[j] > array[j + 1]) {
                // Se o elemento atual for maior que o próximo elemento, ocorre uma inversão de posições.
                // Troca os elementos se o elemento atual for maior que o próximo elemento
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


int main() {
    int narraysize; // Tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &narraysize);

    int array[narraysize]; // Declara o vetor com o índice do tamanho, onde o usuário preenche o vetor
    printf("Digite os elementos do vetor: ");
    for (int i = 0; i < narraysize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    bubbleSort(array, narraysize); // chama o método de ordenação Bubble Sort

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
