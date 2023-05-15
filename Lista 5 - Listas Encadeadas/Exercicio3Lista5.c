#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;
} Numeros; // Define a estrutura Alunos, com as informa��es dos elementos

typedef struct No {
    Numeros num;
    struct No* proximo;
} No; // Define a estrutura No, que representa um n� da lista encadeada, aonde cada n� � um elemento (cliente) da lista

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirNumero(ListaEncadeada* lista, int numentrada) { // Inserir Elementos
    // Aloca a mem�ria para o novo n�, o novo n�mero
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->num.numero = numentrada; // Preenche as informa��es do novo aluno
    novoNo->proximo = NULL; // Como h� um novo n�, o pr�ximo ainda n�o foi definido
    /**
    Isso � importante porque, ao percorrer a lista encadeada posteriormente, o programa pode verificar se
    o ponteiro proximo � NULL, o que indica que o n� atual � o �ltimo n� da lista e n�o h� mais n�s a seguir.
    */

    // Se a lista estiver vazia, o novo n� se torna o primeiro
    if (lista->primeiro == NULL) {
        lista->primeiro = novoNo;
    } else {
        // Percorrer a lista at� o �ltimo n�
        No* atual = lista->primeiro;
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

float calcularMedia(ListaEncadeada* lista) {
    // Se a lista estiver vazia, o novo n� se torna o primeiro
    if (lista->primeiro == NULL) {
        printf("Lista vazia.\n");
        return 0;
    } else {
    int soma = 0; // Inicializa a soma
    No* atual = lista->primeiro; // Come�a pelo primeiro elemento pelo ponteiro atual
    while (atual != NULL) { // Percorre a lista
    soma += atual->num.numero; // Pelo ponteiro atual da struct No, acessa o campo ponteiro num, e depois o campo numero, fazendo a soma dos mesmos
    atual = atual->proximo; // Continua apontando para o pr�ximo para continuar a soma at� o final
    }
    return (float) soma/lista->tamanho; // Retorna
    }
}

int encontrarMenor(ListaEncadeada* lista) {
    // Se a lista estiver vazia, o novo n� se torna o primeiro
    if (lista->primeiro == NULL) {
        printf("Lista vazia.\n");
        return 0;
    } else {
    int menor = lista->primeiro->num.numero; // Inicializa a variavel do menor utilizando o ponteiro lista da struct da ListaEncadeada, que acessa a struct No pelo ponteiro primeiro, e depois o campo ponteiro num para acessar o campo numero
    No* atual = lista->primeiro; // Come�a pelo primeiro elemento pelo ponteiro atual
    while (atual != NULL) { // Percorre a lista
    if (menor > atual->num.numero){ // Compara se o valor do campo numero da struct No (ponteiro num), acessada pelo ponteiro atual � menor que menor
    menor = atual->num.numero; // Ent�o esse � o menor
    }
    atual = atual->proximo; // Continua apontando para o pr�ximo para continuar a soma at� o final
    }
    return menor; // Retorna
    }
}

int encontrarMaior(ListaEncadeada* lista) { // Faz o mesmo que a fun��o anterior, s� que retorna o maior valor
    // Se a lista estiver vazia, o novo n� se torna o primeiro
    if (lista->primeiro == NULL) {
        printf("Lista vazia.\n");
        return 0;
    } else {
    int maior = lista->primeiro->num.numero; // Inicializa a variavel do maior utilizando o ponteiro lista da struct da ListaEncadeada, que acessa a struct No pelo ponteiro primeiro, e depois o campo ponteiro num para acessar o campo numero
    No* atual = lista->primeiro;
    while (atual != NULL) {
    if (maior < atual->num.numero){ // Agora compara se o valor do campo numero da struct No (ponteiro num), acessada pelo ponteiro atual � maior que o maior
    maior = atual->num.numero;
    }
    atual = atual->proximo;
    }
    return maior;
    }
}


int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL;
    lista.tamanho = 0;

    int numentrada;
    char continuar = 'S'; // Vari�vel para controlar a condi��o de parada

    printf("Digite os numeros (digite 'N' ou 'n' para parar):\n");

    while (continuar != 'N' && continuar != 'n') {
        printf("Numero: ");
        scanf("%d", &numentrada);

        inserirNumero(&lista, numentrada);

        printf("Continuar? (S/N): ");
        scanf(" %c", &continuar);
    }
float media = calcularMedia(&lista);
int menorvalor = encontrarMenor(&lista);
int maiorvalor = encontrarMaior(&lista);
printf("A media eh de: %f\n",media);
printf("O menor valor eh: %d\n",menorvalor);
printf("O maior valor eh: %d\n",maiorvalor);
return 0;
}

