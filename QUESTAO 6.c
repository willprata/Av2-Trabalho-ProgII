#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "cidades.txt"
typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;
void incluirCidade() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Cidade cidade;
    printf("Digite o código da cidade: ");
    scanf("%d", &cidade.codigo);
    getchar();  
    printf("Digite o nome da cidade: ");
    fgets(cidade.nome, sizeof(cidade.nome), stdin);
    cidade.nome[strcspn(cidade.nome, "\n")] = '\0'; 
    printf("Digite o nome do estado: ");
    fgets(cidade.estado, sizeof(cidade.estado), stdin);
    cidade.estado[strcspn(cidade.estado, "\n")] = '\0'; 
    printf("Digite a população da cidade: ");
    scanf("%d", &cidade.populacao);
    fprintf(file, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    fclose(file);
    printf("Cidade adicionada com sucesso!\n");
}
void alterarCidade() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    int codigo;
    printf("Digite o código da cidade que deseja alterar: ");
    scanf("%d", &codigo);
    Cidade cidade;
    int encontrado = 0;
    while (fscanf(file, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            printf("Cidade encontrada! Digite os novos dados.\n");
            printf("Novo nome da cidade: ");
            getchar();  
            fgets(cidade.nome, sizeof(cidade.nome), stdin);
            cidade.nome[strcspn(cidade.nome, "\n")] = '\0';
            printf("Novo nome do estado: ");
            fgets(cidade.estado, sizeof(cidade.estado), stdin);
            cidade.estado[strcspn(cidade.estado, "\n")] = '\0';
            printf("Nova população da cidade: ");
            scanf("%d", &cidade.populacao);
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
            encontrado = 1;
        } else {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Dados da cidade atualizados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade não encontrada.\n");
    }
}
void excluirCidade() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    int codigo;
    printf("Digite o código da cidade que deseja excluir: ");
    scanf("%d", &codigo);
    Cidade cidade;
    int encontrado = 0;
    while (fscanf(file, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo != codigo) {
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("Cidade excluída com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade não encontrada.\n");
    }
}
void consultarCidade() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int codigo;
    printf("Digite o código da cidade que deseja consultar: ");
    scanf("%d", &codigo);
    Cidade cidade;
    int encontrado = 0;
    while (fscanf(file, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        if (cidade.codigo == codigo) {
            printf("Código: %d\n", cidade.codigo);
            printf("Nome: %s\n", cidade.nome);
            printf("Estado: %s\n", cidade.estado);
            printf("População: %d\n", cidade.populacao);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Cidade não encontrada.\n");
    }
    fclose(file);
}
void listarCidades() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Cidade cidade;
    printf("Lista de cidades cadastradas:\n");
    while (fscanf(file, "%d,%49[^,],%29[^,],%d\n", &cidade.codigo, cidade.nome, cidade.estado, &cidade.populacao) != EOF) {
        printf("Código: %d\n", cidade.codigo);
        printf("Nome: %s\n", cidade.nome);
        printf("Estado: %s\n", cidade.estado);
        printf("População: %d\n\n", cidade.populacao);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Incluir cidade\n");
        printf("2. Alterar dados de cidade\n");
        printf("3. Excluir cidade\n");
        printf("4. Consultar cidade\n");
        printf("5. Listar todas as cidades\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                incluirCidade();
                break;
            case 2:
                alterarCidade();
                break;
            case 3:
                excluirCidade();
                break;
            case 4:
                consultarCidade();
                break;
            case 5:
                listarCidades();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
