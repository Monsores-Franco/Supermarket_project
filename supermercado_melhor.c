#include <stdio.h>
#include <string.h>

typedef struct {
    char numero_pedido[10];
    char cod_produto[10];
    char cod_cliente[10];
    int quantidade;
    float total;
    char data[11];
} pedido;

typedef struct {
    char cod_cliente[10];
    char razao_social[40];
    char cnpj[19];
    char inscricao_estadual[15];
    char endereco[25];
    char telefone[15];
    char email[20];
} cliente;

typedef struct {
    char cod_produto[10];
    char nome_prod[40];
    float preco;
} produto;

void inserir_produto(produto *prod);
void produto_ordem_crescente(produto *p_produto, int num_prod);

void inserir_cliente(cliente *cli, int num_cli);
void ordenar_cliente(cliente *cli, int num_cliente);

void inserir_pedido(pedido *ped, int num_ped, cliente *cli, int num_cli);

int main() {
    FILE *arquivo_produto;
    FILE *arquivo_pedido;
    FILE *arquivo_cliente;
    arquivo_produto = fopen("arquivo_produto.txt", "wb");
    arquivo_pedido = fopen("arquivo_pedido.txt", "wb");
    arquivo_cliente = fopen("arquivo_cliente.txt", "wb");
    if (arquivo_cliente == NULL) {
        perror("erro ao abrir arquivo_cliente");
        return 1;
    }
    if (arquivo_produto == NULL) {
        perror("erro ao abrir arquivo_produto");
        return 1;
    }
    if (arquivo_pedido == NULL) {
        perror("erro ao abrir arquivo_pedido");
        return 1;
    }

    produto tabela[4];
    cliente clientes[4];
    pedido pedidos[4];
    char opcao;
    int num_produto = 0;
    int num_cliente = 0;
    int num_pedido = 0;
    do {
        printf("escolha uma opção:\n");
        printf("p - inserir produto\n");
        printf("c - inserir cliente\n");
        printf("l - inserir pedido\n");
        printf("s - sair\n");
        scanf(" %c", &opcao);
        getchar();
        switch (opcao) {
            case 'p':
                inserir_produto(&tabela[num_produto]);
                num_produto++;
                break;
            case 'c':
                inserir_cliente(&clientes[num_cliente], num_cliente);
                num_cliente++;
                break;
            case 'l':
                inserir_pedido(pedidos, num_pedido, clientes, num_cliente);
                num_pedido++;
                break;
            case 's':
                break;
        }

    } while (opcao != 's');

    produto_ordem_crescente(tabela, num_produto);
    ordenar_cliente(clientes, num_cliente);

    for (int i = 0; i < num_produto; i++) { //produto
        fprintf(arquivo_produto, "código: %s\n", tabela[i].cod_produto);
        fprintf(arquivo_produto, "nome do produto: %s\n", tabela[i].nome_prod);
        fprintf(arquivo_produto, "preço: %.2f\n", tabela[i].preco);
        fprintf(arquivo_produto, "\n");
    }
    for (int i = 0; i < num_cliente; i++) {  //cliente
        fprintf(arquivo_cliente, "código do cliente: %s\n", clientes[i].cod_cliente);
        fprintf(arquivo_cliente, "Razão social: %s\n", clientes[i].razao_social);
        fprintf(arquivo_cliente, "CNPJ: %s\n", clientes[i].cnpj);
        fprintf(arquivo_cliente, "Inscrição Estadual do cliente: %s\n", clientes[i].inscricao_estadual);
        fprintf(arquivo_cliente, "Endereço do cliente: %s\n", clientes[i].endereco);
        fprintf(arquivo_cliente, "Telefone do cliente: %s\n", clientes[i].telefone);
        fprintf(arquivo_cliente, "E-mail do cliente: %s\n", clientes[i].email);
        fprintf(arquivo_cliente, "\n");
    }
    for (int i = 0; i < num_pedido; i++) { //pedido
        fprintf(arquivo_pedido, "Número do pedido: %s\n", pedidos[i].numero_pedido);
        fprintf(arquivo_pedido, "Código do produto: %s\n", pedidos[i].cod_produto);
        fprintf(arquivo_pedido, "Código do cliente: %s\n", pedidos[i].cod_cliente);
        fprintf(arquivo_pedido, "Quantidade: %d\n", pedidos[i].quantidade);
        fprintf(arquivo_pedido, "Total: %.2f\n", pedidos[i].total);
        fprintf(arquivo_pedido, "Data do pedido: %s\n", pedidos[i].data);
        fprintf(arquivo_pedido, "\n");
    }

    fclose(arquivo_cliente);
    fclose(arquivo_produto);
    fclose(arquivo_pedido);
    return 0;
}

void produto_ordem_crescente(produto *p_produto, int num_prod) {
    int i, j;
    produto temp;

    for (j = 0; j < num_prod; j++) {
        for (i = (j + 1); i < num_prod; i++) {
            if (strcmp(p_produto[j].cod_produto, p_produto[i].cod_produto) > 0) { // Altere para '>'
                temp = p_produto[j];
                p_produto[j] = p_produto[i];
                p_produto[i] = temp;
            }
        }
    }
}

void inserir_produto(produto *prod) {
    printf("digite o codigo do produto: ");
    fgets(prod->cod_produto, sizeof(prod->cod_produto), stdin);
    prod->cod_produto[strcspn(prod->cod_produto, "\n")] = '\0';

    printf("digite o nome do produto: ");
    fgets(prod->nome_prod, sizeof(prod->nome_prod), stdin);
    prod->nome_prod[strcspn(prod->nome_prod, "\n")] = '\0';

    printf("digite o preço do produto: ");
    scanf("%f", &prod->preco);
    getchar();
}

void inserir_cliente(cliente *cli, int num_cli) {
    printf("codigo do cliente: %d", (num_cli + 1));
    fgets(cli->cod_cliente, sizeof(cli->cod_cliente), stdin);
    cli->cod_cliente[strcspn(cli->cod_cliente, "\n")] = '\0';

    printf("razao social do cliente: %d", (num_cli + 1));
    fgets(cli->razao_social, sizeof(cli->razao_social), stdin);
    cli->razao_social[strcspn(cli->razao_social, "\n")] = '\0';

    printf("CPNJ do cliente: %d", (num_cli + 1));
    fgets(cli->cnpj, sizeof(cli->cnpj), stdin);
    cli->cnpj[strcspn(cli->cnpj, "\n")] = '\0';

    printf("Inscrição Estadual do cliente: %d", (num_cli + 1));
    fgets(cli->inscricao_estadual, sizeof(cli->inscricao_estadual), stdin);
    cli->inscricao_estadual[strcspn(cli->inscricao_estadual, "\n")] = '\0';

    printf("Endereço do cliente: %d", (num_cli + 1));
    fgets(cli->endereco, sizeof(cli->endereco), stdin);
    cli->endereco[strcspn(cli->endereco, "\n")] = '\0';

    printf("Telefone do cliente: %d", (num_cli + 1));
    fgets(cli->telefone, sizeof(cli->telefone), stdin);
    cli->telefone[strcspn(cli->telefone, "\n")] = '\0';

    printf("E-mail do cliente: %d", (num_cli + 1));
    fgets(cli->email, sizeof(cli->email), stdin);
    cli->email[strcspn(cli->email, "\n")] = '\0';
}

void ordenar_cliente(cliente *cli, int num_cliente) {
    int i, j;
    cliente temp;

    for (j = 0; j < num_cliente; j++) {
        for (i = (j + 1); i < num_cliente; i++) {
            if (strcmp(cli[j].cod_cliente, cli[i].cod_cliente) > 0) {
                temp = cli[j];
                cli[j] = cli[i];
                cli[i] = temp;
            }
        }
    }
}

void inserir_pedido(pedido *ped, int num_ped, cliente *cli, int num_cli) {
    int cliente_encontrado = 0;
    printf("Digite o código do cliente: ");
    char cod_cliente[10];
    fgets(cod_cliente, sizeof(cod_cliente), stdin);
    cod_cliente[strcspn(cod_cliente, "\n")] = '\0';

    for (int i = 0; i < num_cli; i++) {
        if (strcmp(cod_cliente, cli[i].cod_cliente) == 0) {
            cliente_encontrado = 1;
            break;
        }
    }

    if (cliente_encontrado == 1) {
        strcpy(ped[num_ped].cod_cliente, cod_cliente);
        printf("Digite o número do pedido: \n");
        fgets(ped[num_ped].numero_pedido, sizeof(ped[num_ped].numero_pedido), stdin);
        ped[num_ped].numero_pedido[strcspn(ped[num_ped].numero_pedido, "\n")] = '\0';

        printf("Digite o código do produto: \n");
        fgets(ped[num_ped].cod_produto, sizeof(ped[num_ped].cod_produto), stdin);
        ped[num_ped].cod_produto[strcspn(ped[num_ped].cod_produto, "\n")] = '\0';

        printf("Digite a quantidade: \n");
        scanf("%d", &ped[num_ped].quantidade);

        printf("Digite o total: \n");
        scanf("%f", &ped[num_ped].total);

        printf("Digite a data (no formato DD/MM/AAAA): \n");
        getchar();
        fgets(ped[num_ped].data, sizeof(ped[num_ped].data), stdin);
        ped[num_ped].data[strcspn(ped[num_ped].data, "\n")] = '\0';
    } else {
        printf("Cliente com o código %s não encontrado.\n", cod_cliente);
    }
}