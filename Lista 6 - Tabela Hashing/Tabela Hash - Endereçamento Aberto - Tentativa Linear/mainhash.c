#include <stdio.h>
#include "tabelahash.h"

int main() {
    int tamanhoTabela;
    printf("Digite o tamanho da tabela hash: ");
    scanf("%d", &tamanhoTabela);
    TabelaHash* tabela = criarTabelaHash(tamanhoTabela);

    int opcao = 0;
    int chave, chave1, chave2, valor;

    while (opcao != 8) {
        printf("\n----- Menu -----\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Buscar elemento\n");
        printf("4. Procurar maior e menor valor\n");
        printf("5. Imprimir\n");
        printf("6. Trocar dois elementos de posição\n");
        printf("7. Contar Espacos Vazios\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserir(tabela, chave, valor);
                printf("Elemento inserido com sucesso!\n");
                break;
            case 2:
                printf("Digite a chave do elemento a ser removido: ");
                scanf("%d", &chave);
                remover(tabela, chave);
                printf("Elemento removido com sucesso!\n");
                break;
            case 3:
                printf("Digite a chave do elemento a ser buscado: ");
                scanf("%d", &chave);
                valor = buscar(tabela, chave);
                if (valor != -1) {
                    printf("Valor encontrado: %d\n", valor);
                } else {
                    printf("Elemento nao encontrado!\n");
                }
                break;
            case 4:
                printf("Maior valor: %d\n", procurarMaior(tabela));
                printf("Menor valor: %d\n", procurarMenor(tabela));
                break;
            case 5:
                imprimirTabelaHash(tabela);
                break;
            case 6:
                    printf("Digite a chave do primeiro elemento: ");
                    scanf("%d", &chave1);
                    printf("Digite a chave do segundo elemento: ");
                    scanf("%d", &chave2);
                    trocarPosicaoElementos(tabela, chave1, chave2);
                break;
            case 7:
                printf("Espacos vazios: %d\n", contarEspacosVazios(tabela));
                break;
            case 8:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
