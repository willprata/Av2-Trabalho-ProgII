#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "veiculos.dat"
typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;
void adicionarVeiculo() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Veiculo veiculo;
    printf("Digite o ID do veículo: ");
    scanf("%d", &veiculo.id);
    getchar(); 
    printf("Digite o modelo do veículo: ");
    fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';  
    printf("Digite a placa do veículo: ");
    fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
    veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
    printf("Digite o ano de fabricação do veículo: ");
    scanf("%d", &veiculo.ano);
    fwrite(&veiculo, sizeof(Veiculo), 1, file);
    fclose(file);
    printf("Veículo adicionado com sucesso!\n");
}
void alterarVeiculo() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int id;
    printf("Digite o ID do veículo que deseja alterar: ");
    scanf("%d", &id);
    Veiculo veiculo;
    int encontrado = 0;
    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id == id) {
            printf("Veículo encontrado! \n");
            printf("Novo modelo: ");
            getchar(); 
            fgets(veiculo.modelo, sizeof(veiculo.modelo), stdin);
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            printf("Nova placa: ");
            fgets(veiculo.placa, sizeof(veiculo.placa), stdin);
            veiculo.placa[strcspn(veiculo.placa, "\n")] = '\0';
            printf("Novo ano de fabricação: ");
            scanf("%d", &veiculo.ano);
            fseek(file, -sizeof(Veiculo), SEEK_CUR); 
            fwrite(&veiculo, sizeof(Veiculo), 1, file);
            printf("Dados do veículo atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Veículo não encontrado.\n");
    }
    fclose(file);
}
void excluirVeiculo() {
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
    printf("Digite o ID do veículo que deseja excluir: ");
    scanf("%d", &id);
    Veiculo veiculo;
    int encontrado = 0;
    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id != id) {
            fwrite(&veiculo, sizeof(Veiculo), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Veículo excluído com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("Veículo não encontrado.\n");
    }
}
void consultarVeiculo() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char placa[10];
    printf("Digite a placa do veículo que deseja consultar: ");
    getchar(); 
    fgets(placa, sizeof(placa), stdin);
    placa[strcspn(placa, "\n")] = '\0'; 
    Veiculo veiculo;
    int encontrado = 0;
    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (strcmp(veiculo.placa, placa) == 0) {
            printf("ID: %d\n", veiculo.id);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Placa: %s\n", veiculo.placa);
            printf("Ano de fabricação: %d\n", veiculo.ano);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Veículo não encontrado.\n");
    }
    fclose(file);
}
void listarVeiculos() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Veiculo veiculo;
    printf("Lista de veículos cadastrados:\n");
    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        printf("ID: %d\n", veiculo.id);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ano de fabricação: %d\n\n", veiculo.ano);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar um novo veículo\n");
        printf("2. Alterar dados de um veículo\n");
        printf("3. Excluir um veículo\n");
        printf("4. Consultar informações de um veículo\n");
        printf("5. Listar todos os veículos\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                alterarVeiculo();
                break;
            case 3:
                excluirVeiculo();
                break;
            case 4:
                consultarVeiculo();
                break;
            case 5:
                listarVeiculos();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
