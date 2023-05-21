#include <stdio.h>

void selectionSort(int array[], int narraysize) {
    for (int i = 0; i < narraysize - 1; i++) {
        int firstnonorderedelement = i;
        for (int j = i + 1; j < narraysize; j++) {
            if (array[j] < array[firstnonorderedelement]) {
                firstnonorderedelement = j;
            }
        }

        if (firstnonorderedelement != i) {
            int temp = array[i];
            array[i] = array[firstnonorderedelement];
            array[firstnonorderedelement] = temp;
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

    selectionSort(array, narraysize);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
