#include <stdio.h>
#include <stdlib.h>
#ifndef ARVOREEX2ATE8_H
#define ARVOREEX2ATE8_H

struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
};

struct No* criarNo(int dado) { // Cria n� da �rvore recebendo
    struct No* novoNo = (struct No*)malloc(sizeof(struct No)); // Aloca mem�ria dinamicamente pro novo n�
    novoNo->dado = dado; // Inicializa o novo n�, e seus ramos esquerdos e direitos com NULL, enquanto n�o existem
    novoNo->esquerda = novoNo->direita = NULL;
    return novoNo;
}

struct No* inserir(struct No* raiz, int dado) { // Recebe o ponteiro para a ra�z da �rvore e um valor como argumento
    if (raiz == NULL) {
        return criarNo(dado); // Se a ra�z for nula, ent�o n�o tem n�s, a inser��o � feita diretamente no �nico novo n� criado
    }
    if (dado < raiz->dado) { // Se a ra�z n�o for nula, e o valor fornecido � menor que a ra�z
        raiz->esquerda = inserir(raiz->esquerda, dado); // Ser� inserido recursivamente na sub �rvore esquerda
    } else if (dado > raiz->dado) { // Se for maior que a ra�z
        raiz->direita = inserir(raiz->direita, dado); // Inserido recursivamente na sub �rvore direita
    }
    return raiz;
}

/**
Fun��o para encontrar o n� m�nimo em uma sub-�rvore para o uso da fun��o de remover.
Ela verifica se h� n�s na �rvore e na sub-�rvore, atualizando o atual tamb�m para a sub-�rvore, e isso � feito repetidamente at�
que n�o haja mais n�s para verificar, retornando o valor menor na sub-�rvore.
*/
struct No* encontrarNoMinimo(struct No* no) {
    struct No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

struct No* removerNo(struct No* raiz, int dado) { // Remove um n� da �rvore
    if (raiz == NULL) { // Se n�o houver ra�z ou o valor n�o foi encontrado na �rvore
        return raiz; // Retorna sem modifica��o
    }
    // Se n�o for nenhum dos 2 casos: Localizando o n� a ser removido e atualiza a estrutura da �rvore
    if (dado < raiz->dado) {
        raiz->esquerda = removerNo(raiz->esquerda, dado);
    } else if (dado > raiz->dado) {
        raiz->direita = removerNo(raiz->direita, dado);
    } else {
        if (raiz->esquerda == NULL) { // N� possui apenas filho direito ou nenhum filho
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) { // N� possui apenas filho esquerdo
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        struct No* temp = encontrarNoMinimo(raiz->direita); // N� possui dois filhos
        raiz->dado = temp->dado; // Substitui o dado do n� a ser removido pelo dado do n� m�nimo
        raiz->direita = removerNo(raiz->direita, temp->dado); // Remove o n� m�nimo
    }
    return raiz;
}

struct No* buscarNo(struct No* raiz, int dado) { // Exercicio 4
    while (raiz != NULL) { // Recebe o ponteiro para a ra�z e um valor inteiro a ser buscado na �rvore, enquanto todos os n�s n�o s�o verificados:
        if (dado == raiz->dado) { // Se enfim o valor inteiro buscado � encontrado na �rvore, retorna o ponteiro para o n�
            return raiz;
        } else if (dado < raiz->dado) { // Localiza o n� a ser buscado, se for menor, est� na sub �rvore esquerda, atualizando o ponteiro para ela
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita; // Se for maior, est� na direita, ent�o faz o mesmo que acima, s� que atualizando para a sub �rvore da direita
        } // Move-se para a esquerda e para a direita at� que o n� seja encontrado
    }
    return NULL; // Se o valor dado n�o for encontrado na �rvore, ou seja, quando o loop terminar e a raiz for nula, a fun��o retorna NULL para indicar que o valor n�o foi encontrado na �rvore.
}

struct No* encontrarPai(struct No* raiz, int dado) { // Exercicio 5
    struct No* pai = NULL; // A fun��o recebe o ponteiro para a �rvore e um valor como argumento, inicializa em seguida a vari�vel pai
    while (raiz != NULL && raiz->dado != dado) { // Enquanto a ra�z n�o for nula, e ainda tiver n�s a serem verificados e o valor do n� n�o for encontrado
        pai = raiz; // Atribui-se o valor atual da ra�z a vari�vel pai
        if (dado < raiz->dado) { // Atualiza o ponteiro ra�z para apontar a dire��o para o n� que estamos buscando e ent�o, a sub �rvore que temos de olhar, enquanto pai det�m o n� anterior as sub �rvores
            raiz = raiz->esquerda;
        } else {
            raiz = raiz->direita;
        }
    }
    return pai;
}

struct No* encontrarIrmao(struct No* raiz, int valor) { // Exercicio 2
    struct No* no = buscarNo(raiz, valor); // A variavel n� recebe o resultado da fun��o buscar n� que retorna o ponteiro para o n� encontrado
    if (no == NULL || raiz == NULL) {
        return NULL;  // N� n�o encontrado ou raiz � nula
    }
    struct No* pai = encontrarPai(raiz, valor); // Vari�vel pai recebe o resultado da fun��o encontrarPai, que retorna o pai
    if (pai == NULL) { // Se pai for nulo
        return NULL;  // N� � a raiz, n�o tem irm�o
    }
    // Se n�o for:
    if (pai->esquerda != NULL && pai->esquerda->dado == valor) { // Checa se o n� a esquerda do pai n�o � nulo e se � igual ao valor informado, se for:
        return pai->direita;  // Retorna o n� direito j� que o valor especificado est� � esquerda
    } else {
        return pai->esquerda;  // Caso contr�rio, retorna o n� esquerdo, j� que o valor especificado est� � direita
    }
}


void imprimirCaminho(struct No* raiz, int dado) { // Exercicio 6
    while (raiz != NULL) { // Enquanto a ra�z n�o for nula, e n�o tiver todos os n�s percorridos
        printf("%d ", raiz->dado); // Imprime-se o valor do n� atual
        if (dado == raiz->dado) { // Se o valor do n� atual � igual ao valor especificado, significa que o caminho j� foi percorrido
            break;
        } else if (dado < raiz->dado) { // Se n�o for igual, atualiza o ponteiro ra�z para determinar em qual dire��o seguir
            raiz = raiz->esquerda; // Para a sub �rvore esquerda, se for menor que o valor do n� atual
        } else {
            raiz = raiz->direita; // E para a direita, se for maior
        }
    }
    printf("\n");
}

int contarMaiores(struct No* raiz, int dado) { // Exercicio 7
    if (raiz == NULL) { // Se a ra�z � nula, a �rvore n�o tem n�s, ent�o retorna 0
        return 0;
    }
    if (raiz->dado <= dado) { // Compara para ver se o valor do n� atual � menor que o valor de refer�ncia especificado
        return contarMaiores(raiz->direita, dado); // Se for, chama recursivamente a fun��o passando a contagem para a ra�z direita, que � aonde est�o os n�s maiores que o valor de refer�ncia
    }
    return 1 + contarMaiores(raiz->esquerda, dado) + contarMaiores(raiz->direita, dado); // Se o valor do n� atual � maior, ent�o soma 1 a contagem da soma do resultado da fun��o que percorre as sub �rvores esquerda e direita
}

int calcularAltura(struct No* raiz) { // Exercicio 8
    if (raiz == NULL) { // Se a ra�z � nula, a �rvore n�o tem n�s, ent�o retorna 0
        return 0;
    }
    int alturaEsquerda = calcularAltura(raiz->esquerda); // Chama recursivamente a fun��o para calcular a altura das sub �rvores esq e dir
    int alturaDireita = calcularAltura(raiz->direita);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita); // Se a altura da sub�rvore esquerda for maior que a altura da sub�rvore direita, retornamos alturaEsquerda, caso contr�rio, retornamos alturaDireita.
    // E ent�o, � adicionado 1 ao valor da altura mais alta para incluir a pr�pria raiz na contagem
}

void imprimirEmOrdem(struct No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        imprimirEmOrdem(raiz->direita);
    }
}
/**
Fun��o para impress�o em pr�-ordem, imprimindo a ra�z, depois checando primeiro se h� n�s esquerdos e depois se h� n�s direitos;
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
Fun��o para impress�o em p�s-ordem, checando primeiro se h� n�s esquerdos e depois se h� n�s direitos, imprimindo-os e depois a ra�z.
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
Fun��o para imprimir simetricamente a �rvore, didivindo-a perfeitamente em dois, come�ando a verificar os n�s esquerdos, depois
a ra�z, e depois os direitos. Ou seja, da esquerda pra direita.
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
A fun��o checa para ver se a �rvore possui n�s, se sim, contabiliza o primeiro n�, a pr�pria ra�z, e chama a si recursivamente
para calcular os outros n�s da esquerda e direita, somando ao final
*/
int contarNos(struct No* raiz) {
    if (raiz == NULL) { // Se a ra�z for nula ent�o retorna 0, n�o h� n�s
        return 0;
    }
    return 1 + contarNos(raiz->esquerda) + contarNos(raiz->direita); // Calcula a ra�z + n�s da sub-�rvore da esquerda e as da direita
}
#endif
