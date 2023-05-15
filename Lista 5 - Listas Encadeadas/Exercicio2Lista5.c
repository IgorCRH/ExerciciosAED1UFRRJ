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

void exibirListaInversa(No* atual) {
    if (atual == NULL) { // Verifica se chegamos ao final da lista
        return;  // Se chegarmos ao final da lista (n� atual � NULL), retorna
    }
    exibirListaInversa(atual->proximo);  // Caso ainda n�o chegar ao final, faz chamada recursiva para a pr�pria fun��o e o pr�ximo n�, ou seja o �ltimo n� � chamado primeiro
    printf("Matr�cula: %d, Nome: %s\n", atual->aluno.matricula, atual->aluno.nome);
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
printf("Exibindo a lista em ordem inversa:\n");
exibirListaInversa(lista.primeiro);


    return 0;
}
