#include <stdio.h>

void insertionSort(int array[], int narraysize, int i) {
    if (i == narraysize) { // Condi��o de parada da recurs�o, quando 'i' chegar ao tamanho do vetor
        return;
    }
    int temp = array[i]; // Guarda o valor do elemento atual na vari�vel tempor�ria
    int j = i - 1; // Decrementa J da direita para a esquerda
    while (j >= 0 && array[j] > temp) { // Decrementa J at� chegar ao 0 na esquerda, enquanto os valores a esquerda forem maiores que o atual
        array[j+1] = array[j]; // Desloca e copia os elementos acima para a direita
        j--;
    }
    array[j+1] = temp; // Insere o elemento a ser trocado na posi��o correta, a que restou ap�s deslocar os elementos restantes para a direita

    insertionSort(array, narraysize, i+1); // Chama a recurs�o para o pr�ximo elemento
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

    insertionSort(array, narraysize, 1); // chama o m�todo de ordena��o

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
