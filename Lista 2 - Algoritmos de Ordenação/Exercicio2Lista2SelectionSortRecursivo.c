#include <stdio.h>

// Implementa��o do algoritmo ShellSort
#include <stdio.h>

void selectionSort(int array[], int narraysize, int i) { // Recebe como par�metro o vetor, seu tamanho, e o 'i' com posi��o do primeiro elemento
    if (i == narraysize - 1) {
        return;
    }

    int firstnonorderedelement = i; // Vari�vel firstnonorderedelement � inicializada com o �ndice do primeiro elemento n�o ordenado
    for (int j = i + 1; j < narraysize; j++) { // Loop continuar� enquanto o j (posi��o do pr�ximo, ou posi��o do atual (i) +1) for menor que o tamanho do vetor
        if (array[j] < array[firstnonorderedelement]) { // Se o primeiro elemento for maior que o pr�ximo
            firstnonorderedelement = j; // O primeiro guardar� o valor do pr�ximo
        }
    }

    if (firstnonorderedelement != i) { // Se o elemento n�o est� na posi��o do �ndice atual, ou a troca n�o ser� feita na primeira posi��o
        int temp = array[i]; // O anterior, ou atual, ser� guardado em temp
        array[i] = array[firstnonorderedelement]; // O anterior, ou atual, receber� o menor, ou o pr�ximo valor n�o ordenado
        array[firstnonorderedelement] = temp; // O pr�ximo valor n�o ordenado receber� o que foi alocado, o valor anterior, ou atual de antes
    }

    selectionSort(array, narraysize, i + 1);
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

    selectionSort(array, narraysize, 0);

    printf("\nLista ordenada:\n");
    for (int i = 0; i < narraysize; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
