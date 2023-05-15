#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
} Alunos; // Define a estrutura Alunos, com as informa��es dos elementos

typedef struct No {
    Alunos aluno;
    struct No* proximo;
} No; // Define a estrutura No, que representa um n� da lista encadeada, aonde cada n� � um elemento (cliente) da lista

typedef struct {
    No* primeiro;
    int tamanho;
} ListaEncadeada;

void inserirAluno(ListaEncadeada* lista, int matricula, const char* nome) { // Inserir Elementos
    // Aloca a mem�ria para o novo n�, o novo aluno
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->aluno.matricula = matricula; // Preenche as informa��es do novo aluno
    strncpy(novoNo->aluno.nome, nome, sizeof(novoNo->aluno.nome)); // Recebe a vari�vel nome da main e a aloca no campo nome do Aluno
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


int contarElementos(ListaEncadeada* lista) {
    int contador = 0;
    No* atual = lista->primeiro; // Come�a apontando para o primeiro elemento
    while (atual != NULL) { // Percorre a lista
        contador++; // Incrementa conforme os n�s foram sendo apontados
        atual = atual->proximo; // Atualiza o ponteiro atual para apontar para o pr�ximo n� na lista a cada itera��o, at� o �ltimo n� da lista ser alcan�ado
    }
    return contador;
}

int main() {
    ListaEncadeada lista;
    lista.primeiro = NULL; // Inicializar a lista vazia
    lista.tamanho = 0;

    int continuar = 1;
    while (continuar) {
        int matricula;
        char nome[100];

        printf("Digite a matricula do aluno (ou 0 para parar): ");
        scanf("%d", &matricula);

        if (matricula == 0) {
            continuar = 0;
        } else {
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", nome);

            inserirAluno(&lista, matricula, nome);
        }
    }

    int numElementos = contarElementos(&lista);
    printf("A lista possui %d elementos\n", numElementos);

    // Liberar a mem�ria alocada para os n�s da lista
    No* atual = lista.primeiro;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
