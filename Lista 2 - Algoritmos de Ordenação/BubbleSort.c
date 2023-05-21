#include <stdio.h>

void bubbleSort(int array[], int arraySize) {
    for (int i = 0; i < arraySize - 1; i++) {
        // O loop externo controla a passagem atual no Bubble Sort. Cada passagem coloca o maior elemento no final.
        // Como o maior elemento � colocado na posi��o correta a cada passagem, o tamanho da parte n�o ordenada diminui em 1.

        for (int j = 0; j < arraySize - i - 1; j++) {
            // O loop interno percorre a parte n�o ordenada do vetor.
            // Como o maior elemento j� est� na posi��o correta ap�s cada passagem, n�o � necess�rio comparar com os elementos j� ordenados.
            // A cada itera��o, compara-se o elemento atual com o pr�ximo elemento e realiza a troca se necess�rio.

            if (array[j] > array[j + 1]) {
                // Se o elemento atual for maior que o pr�ximo elemento, ocorre uma invers�o de posi��es.
                // Troca os elementos se o elemento atual for maior que o pr�ximo elemento
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

    int array[narraysize]; // Declara o vetor com o �ndice do tamanho, onde o usu�rio preenche o vetor
    printf("Digite os elementos do vetor: ");
    for (int i = 0; i < narraysize; i++) {
        scanf("%d", &array[i]);
    }

    printf("Lista original:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    bubbleSort(array, narraysize); // chama o m�todo de ordena��o Bubble Sort

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
