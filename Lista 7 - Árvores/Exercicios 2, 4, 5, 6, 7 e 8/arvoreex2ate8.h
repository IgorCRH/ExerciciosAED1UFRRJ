#include <stdio.h>
#include <stdlib.h>
#ifndef ARVOREEX2ATE8_H
#define ARVOREEX2ATE8_H

struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
};

struct No* criarNo(int dado) { // Cria nó da árvore recebendo
    struct No* novoNo = (struct No*)malloc(sizeof(struct No)); // Aloca memória dinamicamente pro novo nó
    novoNo->dado = dado; // Inicializa o novo nó, e seus ramos esquerdos e direitos com NULL, enquanto não existem
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

struct No* inserir(struct No* raiz, int dado) { // Recebe o ponteiro para a raíz da árvore e um valor como argumento
    if (raiz == NULL) {
        return criarNo(dado); // Se a raíz for nula, então não tem nós, a inserção é feita diretamente no único novo nó criado
    }
    if (dado < raiz->dado) { // Se a raíz não for nula, e o valor fornecido é menor que a raíz
        raiz->esquerda = inserir(raiz->esquerda, dado); // Será inserido recursivamente na sub árvore esquerda
    } else if (dado > raiz->dado) { // Se for maior que a raíz
        raiz->direita = inserir(raiz->direita, dado); // Inserido recursivamente na sub árvore direita
    }
    return raiz;
}

/**
Função para encontrar o nó mínimo em uma sub-árvore para o uso da função de remover.
Ela verifica se há nós na árvore e na sub-árvore, atualizando o atual também para a sub-árvore, e isso é feito repetidamente até
que não haja mais nós para verificar, retornando o valor menor na sub-árvore.
*/
struct No* encontrarNoMinimo(struct No* no) {
    struct No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

struct No* removerNo(struct No* raiz, int dado) { // Remove um nó da árvore
    if (raiz == NULL) { // Se não houver raíz ou o valor não foi encontrado na árvore
        return raiz; // Retorna sem modificação
    }
    // Se não for nenhum dos 2 casos: Localizando o nó a ser removido e atualiza a estrutura da árvore
    if (dado < raiz->dado) {
        raiz->esquerda = removerNo(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = removerNo(raiz->direita, dado);
    } else {
        if (raiz->esquerda == NULL) { // Nó possui apenas filho direito ou nenhum filho
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) { // Nó possui apenas filho esquerdo
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct No* temp = encontrarNoMinimo(raiz->direita); // Nó possui dois filhos
        raiz->dado = temp->dado; // Substitui o dado do nó a ser removido pelo dado do nó mínimo
        raiz->direita = removerNo(raiz->direita, temp->dado); // Remove o nó mínimo
    }
    return raiz;
}

struct No* buscarNo(struct No* raiz, int dado) { // Exercicio 4
    while (raiz != NULL) { // Recebe o ponteiro para a raíz e um valor inteiro a ser buscado na árvore, enquanto todos os nós não são verificados:
        if (dado == raiz->dado) { // Se enfim o valor inteiro buscado é encontrado na árvore, retorna o ponteiro para o nó
            return raiz;
        } else if (dado < raiz->dado) { // Localiza o nó a ser buscado, se for menor, está na sub árvore esquerda, atualizando o ponteiro para ela
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita; // Se for maior, está na direita, então faz o mesmo que acima, só que atualizando para a sub árvore da direita
        } // Move-se para a esquerda e para a direita até que o nó seja encontrado
    }
    return NULL; // Se o valor dado não for encontrado na árvore, ou seja, quando o loop terminar e a raiz for nula, a função retorna NULL para indicar que o valor não foi encontrado na árvore.
}

struct No* encontrarPai(struct No* raiz, int dado) { // Exercicio 5
    struct No* pai = NULL; // A função recebe o ponteiro para a árvore e um valor como argumento, inicializa em seguida a variável pai
    while (raiz != NULL && raiz->dado != dado) { // Enquanto a raíz não for nula, e ainda tiver nós a serem verificados e o valor do nó não for encontrado
        pai = raiz; // Atribui-se o valor atual da raíz a variável pai
        if (dado < raiz->dado) { // Atualiza o ponteiro raíz para apontar a direção para o nó que estamos buscando e então, a sub árvore que temos de olhar, enquanto pai detém o nó anterior as sub árvores
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return pai;
}

struct No* encontrarIrmao(struct No* raiz, int valor) { // Exercicio 2
    struct No* no = buscarNo(raiz, valor); // A variavel nó recebe o resultado da função buscar nó que retorna o ponteiro para o nó encontrado
    if (no == NULL || raiz == NULL) {
        return NULL;  // Nó não encontrado ou raiz é nula
    }
    struct No* pai = encontrarPai(raiz, valor); // Variável pai recebe o resultado da função encontrarPai, que retorna o pai
    if (pai == NULL) { // Se pai for nulo
        return NULL;  // Nó é a raiz, não tem irmão
    }
    // Se não for:
    if (pai->esquerda != NULL && pai->esquerda->dado == valor) { // Checa se o nó a esquerda do pai não é nulo e se é igual ao valor informado, se for:
        return pai->direita;  // Retorna o nó direito já que o valor especificado está à esquerda
    } else {
        return pai->esquerda;  // Caso contrário, retorna o nó esquerdo, já que o valor especificado está à direita
    }
}


void imprimirCaminho(struct No* raiz, int dado) { // Exercicio 6
    while (raiz != NULL) { // Enquanto a raíz não for nula, e não tiver todos os nós percorridos
        printf("%d ", raiz->dado); // Imprime-se o valor do nó atual
        if (dado == raiz->dado) { // Se o valor do nó atual é igual ao valor especificado, significa que o caminho já foi percorrido
            break;
        } else if (dado < raiz->dado) { // Se não for igual, atualiza o ponteiro raíz para determinar em qual direção seguir
            raiz = raiz->esquerda; // Para a sub árvore esquerda, se for menor que o valor do nó atual
        } else {
            raiz = raiz->direita; // E para a direita, se for maior
        }
    }
    printf("\n");
}

int contarMaiores(struct No* raiz, int dado) { // Exercicio 7
    if (raiz == NULL) { // Se a raíz é nula, a árvore não tem nós, então retorna 0
        return 0;
    }
    if (raiz->dado <= dado) { // Compara para ver se o valor do nó atual é menor que o valor de referência especificado
        return contarMaiores(raiz->direita, dado); // Se for, chama recursivamente a função passando a contagem para a raíz direita, que é aonde estão os nós maiores que o valor de referência
    }
    return 1 + contarMaiores(raiz->esquerda, dado) + contarMaiores(raiz->direita, dado); // Se o valor do nó atual é maior, então soma 1 a contagem da soma do resultado da função que percorre as sub árvores esquerda e direita
}

int calcularAltura(struct No* raiz) { // Exercicio 8
    if (raiz == NULL) { // Se a raíz é nula, a árvore não tem nós, então retorna 0
        return 0;
    }
    int alturaEsquerda = calcularAltura(raiz->esquerda); // Chama recursivamente a função para calcular a altura das sub árvores esq e dir
    int alturaDireita = calcularAltura(raiz->direita);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita); // Se a altura da subárvore esquerda for maior que a altura da subárvore direita, retornamos alturaEsquerda, caso contrário, retornamos alturaDireita.
    // E então, é adicionado 1 ao valor da altura mais alta para incluir a própria raiz na contagem
}

void imprimirEmOrdem(struct No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}
/**
Função para impressão em pré-ordem, imprimindo a raíz, depois checando primeiro se há nós esquerdos e depois se há nós direitos;
Ou seja, de cima para baixo.
*/
void pre_ordem(struct No* raiz) {
    printf("%d ", raiz->dado);
    if (raiz->esquerda != NULL) {
    pre_ordem(raiz->esquerda);
    }
    if (raiz->direita !=NULL){
    pre_ordem(raiz->direita);
    }
}

/**
Função para impressão em pós-ordem, checando primeiro se há nós esquerdos e depois se há nós direitos, imprimindo-os e depois a raíz.
Ou seja, de baixo para cima.
*/

void pos_ordem(struct No* raiz) {
    if (raiz->esquerda != NULL) {
    pre_ordem(raiz->esquerda);
    }
    if (raiz->direita !=NULL){
    pre_ordem(raiz->direita);
    }
    printf("%d ", raiz->dado);
}

/**
Função para imprimir simetricamente a árvore, didivindo-a perfeitamente em dois, começando a verificar os nós esquerdos, depois
a raíz, e depois os direitos. Ou seja, da esquerda pra direita.
*/
void sim_ordem(struct No* raiz){
    if (raiz->esquerda != NULL) {
    pre_ordem(raiz->esquerda);
    }
    printf("%d ", raiz->dado);
    if (raiz->direita !=NULL){
    pre_ordem(raiz->direita);
    }
}

/**
A função checa para ver se a árvore possui nós, se sim, contabiliza o primeiro nó, a própria raíz, e chama a si recursivamente
para calcular os outros nós da esquerda e direita, somando ao final
*/
int contarNos(struct No* raiz) {
    if (raiz == NULL) { // Se a raíz for nula então retorna 0, não há nós
        return 0;
    }
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita); // Calcula a raíz + nós da sub-árvore da esquerda e as da direita
}
#endif
