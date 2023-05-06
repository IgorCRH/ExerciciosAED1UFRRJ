#include <stdio.h>

void insertionSort(int array[], int narraysize, int i) {
    if (i == narraysize) { // Condição de parada da recursão, quando 'i' chegar ao tamanho do vetor
        return;
    }
    int temp = array[i]; // Guarda o valor do elemento atual na variável temporária
    int j = i - 1; // Decrementa J da direita para a esquerda
    while (j >= 0 && array[j] > temp) { // Decrementa J até chegar ao 0 na esquerda, enquanto os valores a esquerda forem maiores que o atual
        array[j+1] = array[j]; // Desloca e copia os elementos acima para a direita
        j--;
    }
    array[j+1] = temp; // Insere o elemento a ser trocado na posição correta, a que restou após deslocar os elementos restantes para a direita

    insertionSort(array, narraysize, i+1); // Chama a recursão para o próximo elemento
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

    insertionSort(array, narraysize, 1); // chama o método de ordenação

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
