#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
} Numeros;

typedef struct No {
    Numeros num;
    struct No* proximo;
} No;

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirNumero(ListaEncadeada* lista, int numentrada) {
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca a mem�ria para o novo n�, o novo n�mero
    novoNo->num.numero = numentrada; // Preenche o campo numero com o valor numentrada pela main
    novoNo->proximo = NULL; // Como h� um novo n�, o pr�ximo ainda n�o foi definido
    /**
    Isso � importante porque, ao percorrer a lista encadeada posteriormente, o programa pode verificar se
    o ponteiro proximo � NULL, o que indica que o n� atual � o �ltimo n� da lista e n�o h� mais n�s a seguir.
    */

    if (lista->primeiro == NULL) { // Se a lista estiver vazia, o novo n� se torna o primeiro
        lista->primeiro = novoNo;
    } else {
        No* atual = lista->primeiro; // Se n�o, percorre a lista at� o �ltimo n�
        while (atual->proximo != NULL) { // Percorre a lista encadeada
            atual = atual->proximo; // Se n�o for NULL, avan�a para o pr�ximo n�, atualizando o ponteiro atual
            // Atualiza o ponteiro atual para apontar para o pr�ximo n� na lista a cada itera��o, at� o �ltimo n� da lista ser alcan�ado
        }
        // Adicionar o novo n� no final da lista
        atual->proximo = novoNo;
    }
    // Incrementar o tamanho da lista
    lista->tamanho++;
}

void inserirNumeroInverso(ListaEncadeada* lista, int numentrada) { // Cria a segunda lista que ser� preenchida com a ordem inversa da primeira
    No* novoNo = (No*)malloc(sizeof(No)); // Aloca a mem�ria para os elementos que vir�o
    novoNo->num.numero = numentrada; // Preenche
    novoNo->proximo = lista->primeiro; // Define o pr�ximo n� do novo n� como o primeiro n� da lista atual

    lista->primeiro = novoNo; // Define o novo n� como o primeiro n� da lista atual, tornando-o o novo in�cio da lista

    lista->tamanho++; // Incrementa
}

void exibirLista(No* atual) { // Exibe a lista original percorrendo por meio do while
    while (atual != NULL) {
        printf("%d\n", atual->num.numero);
        atual = atual->proximo; // Avan�a para o pr�ximo a cada itera��o para a impress�o, at� chegar ao final
    }
}

void exibirListaInversa(No* atual) { // Exibe a lista original, s� que inversa em nova lista
    if (atual == NULL) { // Verifica se chegamos ao final da lista
        return; // Se chegarmos ao final da lista (n� atual NULL), retorna
    }
    exibirListaInversa(atual->proximo); // Caso ainda n�o chegar ao final, faz chamada recursiva para a pr�pria fun��o e o pr�ximo n�, ou seja o �ltimo n� � chamado primeiro
    printf("%d\n", atual->num.numero);
}

int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL;
    lista.tamanho = 0;

    int numentrada;
    char continuar = 'S';

    printf("Digite os numeros (digite 'N' ou 'n' para parar):\n");

    while (continuar != 'N' && continuar != 'n') {
        printf("Numero: ");
        scanf("%d", &numentrada);

        inserirNumero(&lista, numentrada);

        printf("Continuar? (S/N): ");
        scanf(" %c", &continuar);
    }

    printf("Primeira lista:\n");
    exibirLista(lista.primeiro);

    ListaEncadeada segundaLista;
    segundaLista.primeiro = NULL;
    segundaLista.tamanho = 0;

    No* atual = lista.primeiro;
    while (atual != NULL) {
        inserirNumeroInverso(&segundaLista, atual->num.numero);
        atual = atual->proximo;
    }

    printf("Segunda lista (ordem inversa):\n");
    exibirLista(segundaLista.primeiro);

    return 0;
}
