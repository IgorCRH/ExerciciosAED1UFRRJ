#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

int main() {
    Lista listaClientes;
    int capacidadeInicial = 10; // Capacidade inicial da lista
    inicializarLista(&listaClientes, capacidadeInicial); // Chamada a fun��o para inicializara lista

    int opcao;
    int cpf;
    float valor;
    TCliente novoCliente;

    do {
        printf("\nDigite a opcao desejada:\n");
        printf("1. Verificar se um cliente esta cadastrado\n");
        printf("2. Fazer retirada de uma determinada quantia de um cliente\n");
        printf("3. Inserir um novo cliente\n");
        printf("4. Inserir cliente em uma posicao na lista\n");
        printf("5. Inserir cliente no meio da lista\n");
        printf("6. Retirar um cliente\n");
        printf("7. Imprimir Lista\n");
        printf("8. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf); // L� o CPF do cliente e passa por argumento para a fun��o de buscar CPF do banco.h e checa
                if (buscarLista(&listaClientes, cpf) == -1) { // Se n�o for encontrado
                    printf("Cliente nao cadastrado.\n");
                } else { // Se for
                    printf("Cliente cadastrado.\n");
                }
                break;
            case 2:
                printf("Digite o CPF do cliente: ");
                scanf("%d", &cpf);
                printf("Digite o valor a ser sacado: ");
                scanf("%f", &valor);
                int resultadoSaque = sacarLista(&listaClientes, cpf, valor); // Dentro da lista, passa o o CPF do cliente e passa por argumento para a fun��o de buscar CPF do banco.h e checa
                if (resultadoSaque == 0) { // Se o cliente n�o est� cadastrado
                    printf("Cliente nao encontrado.\n");
                } else if (resultadoSaque == -1) { // Se o saldo n�o for suficiente
                    printf("Saldo insuficiente.\n");
                } else { // Se ele est� cadastrado
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

    if (listaClientes.capacidade == listaClientes.capacidade) {
        int novaCapacidade = listaClientes.capacidade * 2; // Dobra a capacidade da lista
        TCliente* novoArrayClientes = (TCliente*) realloc(listaClientes.dados, novaCapacidade * sizeof(TCliente)); // Muda din�micamente a capacidade
        if (novoArrayClientes != NULL) {
            listaClientes.dados = novoArrayClientes; // Incorpora a nova capacidade a struct Lista
            listaClientes.capacidade = novaCapacidade;
        } else {
            printf("Erro ao realocar memoria.\n");
            exit(1);
        }
    }

    int resultadoInsercao = inserirCliente(&listaClientes, novoCliente); // Checa para ver se a lista est� cheia ou o cliente j� est� cadastrado
    if (resultadoInsercao == 0) { // InserirCliente retorna 0 se a lista estiver cheia, ent�o o inser��o ser� 0, logo:
        printf("Lista cheia.\n");
    } else if (resultadoInsercao == -1) { // InserirCliente retorna -1 se o cliente j� tenha sido cadastrado, ent�o o inser��o ser� -1, logo:
        printf("Cliente ja cadastrado.\n");
    } else { // Se o cliente ainda n�o tiver cadastrado e a lista n�o estiver cheia
        printf("Cliente inserido com sucesso.\n");
    }
    break;
            case 4:
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
    printf("Digite a posicao para inserir o cliente: ");
    scanf("%d", &posicao);

    if (posicao <= 0 || posicao > listaClientes.ultimo + 2) {
        printf("Posicao invalida.\n");
        break;
    }

    if (listaClientes.capacidade == listaClientes.capacidade) {
        int novaCapacidade = listaClientes.capacidade * 2; // Dobra a capacidade da lista
        TCliente* novoArrayClientes = (TCliente*) realloc(listaClientes.dados, novaCapacidade * sizeof(TCliente)); // Muda dinamicamente a capacidade
        if (novoArrayClientes != NULL) {
            listaClientes.dados = novoArrayClientes; // Incorpora a nova capacidade � struct Lista
            listaClientes.capacidade = novaCapacidade;
        } else {
            printf("Erro ao realocar memoria.\n");
            exit(1);
        }
    }

    int resultadoInsercaoMeio = inserirClienteMeio(&listaClientes, novoCliente, posicao); // Chama a fun��o inserirClienteMeio passando a lista, o novo cliente e a posi��o
    if (resultadoInsercaoMeio == 0) { // inserirClienteMeio retorna 0 se a posi��o for inv�lida
        printf("Posicao invalida.\n");
    } else if (resultadoInsercaoMeio == -1) { // inserirClienteMeio retorna -1 se o cliente j� estiver cadastrado
        printf("Cliente ja cadastrado.\n");
    } else { // Cliente inserido com sucesso
        printf("Cliente inserido com sucesso.\n");
    }
                break;
            case 5:
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


    if (listaClientes.capacidade == listaClientes.capacidade) {
        int novaCapacidade = listaClientes.capacidade * 2; // Dobra a capacidade da lista
        TCliente* novoArrayClientes = (TCliente*) realloc(listaClientes.dados, novaCapacidade * sizeof(TCliente)); // Muda dinamicamente a capacidade
        if (novoArrayClientes != NULL) {
            listaClientes.dados = novoArrayClientes; // Incorpora a nova capacidade � struct Lista
            listaClientes.capacidade = novaCapacidade;
        } else {
            printf("Erro ao realocar memoria.\n");
            exit(1);
        }
    }

    int resultadoInsercaonoTermodoMeio = inserirClienteTermodoMeio(&listaClientes, novoCliente); // Chama a fun��o inserirClienteTermodoMeio passando a lista e o novo cliente
    if (resultadoInsercaonoTermodoMeio == -1) { // inserirClienteTermodoMeio retorna 0 se o cliente j� estiver cadastrado
        printf("Cliente ja cadastrado.\n");
    } else if (resultadoInsercaonoTermodoMeio == 0){
printf("Lista Cheia.\n");
 }  else { // Cliente inserido com sucesso
        printf("Cliente inserido com sucesso.\n");
    }
    break;
                break;
case 6:
    printf("Digite o CPF do cliente a ser removido: ");
    scanf("%d", &cpf);
    int resultadoRemocao = removerCliente(&listaClientes, cpf); // Dentro da lista, l� o CPF e passa por argumento para a chamada da fun��o de busca do CPF dentro da fun��o removerCliente
    if (resultadoRemocao == 0) { // RemoveCliente retorna 0 se o CPF n�o for encontrado, logo o Remocao ser� 0, ent�o:
        printf("Cliente nao encontrado.\n");
    } else { // Se o cliente for encontrado, � removido
        printf("Cliente removido com sucesso.\n");
        // Verifica se precisa realocar a mem�ria
        if (listaClientes.capacidade == listaClientes.capacidade/2) {
            int novaCapacidade = listaClientes.capacidade/2; // Faz o mesmo processo de quando se insere um cliente
            TCliente* novoArrayClientes = (TCliente*) realloc(listaClientes.dados, novaCapacidade * sizeof(TCliente));
            if (novoArrayClientes != NULL) {
                listaClientes.dados = novoArrayClientes;
                listaClientes.capacidade = novaCapacidade;
            }
        }
    }
    break;
case 7:
    imprimirLista(&listaClientes);
    break;
case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 8);

    free(listaClientes.dados);

    return 0;
}
