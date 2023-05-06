#include <stdio.h>

// Implementação do algoritmo ShellSort
#include <stdio.h>

void selectionSort(int array[], int narraysize, int i) { // Recebe como parâmetro o vetor, seu tamanho, e o 'i' com posição do primeiro elemento
    if (i == narraysize - 1) {
        return;
    }

    int firstnonorderedelement = i; // Variável firstnonorderedelement é inicializada com o índice do primeiro elemento não ordenado
    for (int j = i + 1; j < narraysize; j++) { // Loop continuará enquanto o j (posição do próximo, ou posição do atual (i) +1) for menor que o tamanho do vetor
        if (array[j] < array[firstnonorderedelement]) { // Se o primeiro elemento for maior que o próximo
            firstnonorderedelement = j; // O primeiro guardará o valor do próximo
        }
    }

    if (firstnonorderedelement != i) { // Se o elemento não está na posição do índice atual, ou a troca não será feita na primeira posição
        int temp = array[i]; // O anterior, ou atual, será guardado em temp
        array[i] = array[firstnonorderedelement]; // O anterior, ou atual, receberá o menor, ou o próximo valor não ordenado
        array[firstnonorderedelement] = temp; // O próximo valor não ordenado receberá o que foi alocado, o valor anterior, ou atual de antes
    }

    selectionSort(array, narraysize, i + 1);
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

    selectionSort(array, narraysize, 0);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
