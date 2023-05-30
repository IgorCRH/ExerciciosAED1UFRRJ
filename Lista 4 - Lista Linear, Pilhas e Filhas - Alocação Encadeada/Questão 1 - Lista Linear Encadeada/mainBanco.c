#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

int main() {
    ListaEncadeada listaClientes;
    inicializarLista(&listaClientes);

    int opcao;
    int cpf;
    float valor;
    TCliente novoCliente;

    do {
        printf("\nDigite a opcao desejada:\n");
        printf("1. Verificar se um cliente esta cadastrado\n");
        printf("2. Fazer retirada de uma determinada quantia de um cliente\n");
        printf("3. Inserir um novo cliente\n");
        printf("4. Retirar um cliente\n");
        printf("5. Listar clientes\n");
        printf("6. Inserir cliente dado uma posicao na lista\n");
        printf("7. Inserir cliente no meio da lista\n");
        printf("8. Imprimir lista de cliente\n");
        printf("9. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf);
                if (buscarLista(&listaClientes, cpf) == -1) {
                    printf("Cliente nao cadastrado.\n");
                } else {
                    printf("Cliente cadastrado.\n");
                }
                break;
            case 2:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf);
                printf("Digite o valor a ser sacado: ");
                scanf("%f", &valor);
                int resultadoSaque = sacarLista(&listaClientes, cpf, valor);
                if (resultadoSaque == 0) {
                    printf("Cliente nao encontrado.\n");
                } else if (resultadoSaque == -1) {
                    printf("Saldo insuficiente.\n");
                } else {
                    printf("Saque realizado com sucesso.\n");
                }
                break;
            case 3:
                printf("Digite o CPF do novo cliente: ");
                scanf("%d", &novoCliente.cpf);
                printf("Digite o nome do novo cliente: ");
                scanf("%s", novoCliente.nome);
                printf("Digite o endereco do novo cliente: ");
                scanf("%s", novoCliente.endereco);
                fflush(stdin);
                printf("Digite o telefone do novo cliente: ");
                scanf("%s", novoCliente.tel);
                fflush(stdin);
                printf("Digite o saldo do novo cliente: ");
                scanf("%f", &novoCliente.saldo);

                int resultadoInsercao = inserirCliente(&listaClientes, novoCliente);
                if (resultadoInsercao == 0) {
                    printf("Erro ao inserir cliente.\n");
                } else if (resultadoInsercao == -1) {
                    printf("Cliente ja cadastrado.\n");
                } else {
                    printf("Cliente inserido com sucesso.\n");
                }
                break;
            case 4:
                printf("Digite o CPF do cliente a ser removido: ");
                scanf("%d", &cpf);
                int resultadoRemocao = removerCliente(&listaClientes, cpf);
                if (resultadoRemocao == 0) {
                    printf("Cliente nao encontrado.\n");
                } else {
                    printf("Cliente removido com sucesso.\n");
                }
                break;
            case 5:
                imprimirLista(&listaClientes);
                break;
            case 6:
        printf("Digite o CPF do novo cliente: ");
        scanf("%d", &novoCliente.cpf);
        printf("Digite o nome do novo cliente: ");
        scanf("%s", novoCliente.nome);
        printf("Digite o endereco do novo cliente: ");
        scanf("%s", novoCliente.endereco);
        fflush(stdin);
        printf("Digite o telefone do novo cliente: ");
        scanf("%s", novoCliente.tel);
        fflush(stdin);
        printf("Digite o saldo do novo cliente: ");
        scanf("%f", &novoCliente.saldo);
        int posicao;
        printf("Digite a posicao de insercao: ");
        scanf("%d", &posicao);

        int InsercaoMeio = inserirClienteMeio(&listaClientes, novoCliente, posicao);
        if (InsercaoMeio == 0) {
            printf("Erro ao inserir cliente.\n");
        } else if (InsercaoMeio == -1) {
            printf("Cliente já cadastrado.\n");
        } else if (InsercaoMeio == -2) {
            printf("Posicao invalida.\n");
        } else {
            printf("Cliente inserido com sucesso.\n");
        }
                break;
            case 7:
                printf("Digite o CPF do novo cliente: ");
        scanf("%d", &novoCliente.cpf);
        printf("Digite o nome do novo cliente: ");
        scanf("%s", novoCliente.nome);
        printf("Digite o endereco do novo cliente: ");
        scanf("%s", novoCliente.endereco);
        fflush(stdin);
        printf("Digite o telefone do novo cliente: ");
        scanf("%s", novoCliente.tel);
        fflush(stdin);
        printf("Digite o saldo do novo cliente: ");
        scanf("%f", &novoCliente.saldo);
        int InsercaoTermodoMeio = inserirClienteTermodoMeio(&listaClientes, novoCliente);
                if (InsercaoTermodoMeio == 0) {
            printf("Erro ao inserir cliente.\n");
        } else if (InsercaoTermodoMeio == -1) {
            printf("Cliente já cadastrado.\n");
        }  else {
            printf("Cliente inserido com sucesso.\n");
        }
                break;
            case 8:
                imprimirLista(&listaClientes);
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 8);

    // Liberar memória dos nós da lista
    No* atual = listaClientes.primeiro;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    return 0;
}
