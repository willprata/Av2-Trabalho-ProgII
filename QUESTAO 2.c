#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "funcionarios.dat"
typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    int salario;
} Funcionario;
void cadastrarFuncionario() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Funcionario funcionario;
    printf("Digite o ID do funcionário: ");
    scanf("%d", &funcionario.id);
    getchar(); 
    printf("Digite o nome do funcionário: ");
    fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
    funcionario.nome[strcspn(funcionario.nome, "\n")] = '\0';  
    printf("Digite o cargo do funcionário: ");
    fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
    funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0'; 
    printf("Digite o salário do funcionário: ");
    scanf("%d", &funcionario.salario);
    fwrite(&funcionario, sizeof(Funcionario), 1, file);
    fclose(file);
    printf("Funcionário cadastrado com sucesso!\n");
}
void alterarFuncionario() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int id;
    printf("Digite o ID do funcionário que deseja alterar: ");
    scanf("%d", &id);
    Funcionario funcionario;
    int encontrado = 0;
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id == id) {
            printf("Funcionário encontrado! \n");
            printf("Novo cargo: ");
            getchar();
            fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
            funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';
            printf("Novo salário: ");
            scanf("%d", &funcionario.salario);
            fseek(file, -sizeof(Funcionario), SEEK_CUR);
            fwrite(&funcionario, sizeof(Funcionario), 1, file);
            printf("Dados atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }
    fclose(file);
}
void excluirFuncionario() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }
    int id;
    printf("Digite o ID do funcionário que deseja excluir: ");
    scanf("%d", &id);
    Funcionario funcionario;
    int encontrado = 0;
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id != id) {
            fwrite(&funcionario, sizeof(Funcionario), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Funcionário excluído com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("Funcionário não encontrado.\n");
    }
}
void consultarFuncionario() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int id;
    printf("Digite o ID do funcionário que deseja consultar: ");
    scanf("%d", &id);
    Funcionario funcionario;
    int encontrado = 0;
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id == id) {
            printf("ID: %d\n", funcionario.id);
            printf("Nome: %s\n", funcionario.nome);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salário: R$ %d\n", funcionario.salario);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }
    fclose(file);
}
void listarFuncionarios() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Funcionario funcionario;
    printf("Lista de funcionários cadastrados:\n");
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        printf("ID: %d\n", funcionario.id);
        printf("Nome: %s\n", funcionario.nome);
        printf("Cargo: %s\n", funcionario.cargo);
        printf("Salário: R$ %d\n\n", funcionario.salario);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar um novo funcionário\n");
        printf("2. Alterar dados de um funcionário\n");
        printf("3. Excluir um funcionário\n");
        printf("4. Consultar informações de um funcionário\n");
        printf("5. Listar todos os funcionários\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarFuncionario();
                break;
            case 2:
                alterarFuncionario();
                break;
            case 3:
                excluirFuncionario();
                break;
            case 4:
                consultarFuncionario();
                break;
            case 5:
                listarFuncionarios();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
