#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "alunos.dat"
typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;
void incluirAluno() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Aluno aluno;
    printf("Digite a matricula: ");
    scanf("%d", &aluno.matricula);
    getchar(); 
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0';  
    printf("Digite o curso: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0'; 
    printf("Digite a idade do aluno: ");
    scanf("%d", &aluno.idade);
    fwrite(&aluno, sizeof(Aluno), 1, file);
    fclose(file);
    printf("Aluno cadastrado com sucesso!\n");
}
void alterarAluno() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int matricula;
    printf("Digite a matricula do aluno que deseja alterar: ");
    scanf("%d", &matricula);
    Aluno aluno;
    int encontrado = 0;
    while (fread(&aluno, sizeof(Aluno), 1, file)) {
        if (aluno.matricula == matricula) {
            printf("Aluno encontrado! \n");
            printf("Novo nome: ");
            getchar(); 
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
            printf("Novo curso: ");
            fgets(aluno.curso, sizeof(aluno.curso), stdin);
            aluno.curso[strcspn(aluno.curso, "\n")] = '\0';
            printf("Nova idade: ");
            scanf("%d", &aluno.idade);
            fseek(file, -sizeof(Aluno), SEEK_CUR); 
            fwrite(&aluno, sizeof(Aluno), 1, file);
            printf("Informações atualizadas com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno não encontrado.\n");
    }
    fclose(file);
}
void excluirAluno() {
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
    int matricula;
    printf("Digite a matricula do aluno que deseja excluir: ");
    scanf("%d", &matricula);
    Aluno aluno;
    int encontrado = 0;
    while (fread(&aluno, sizeof(Aluno), 1, file)) {
        if (aluno.matricula != matricula) {
            fwrite(&aluno, sizeof(Aluno), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Aluno excluído com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("Aluno não encontrado.\n");
    }
}
void consultarAluno() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int matricula;
    printf("Digite a matricula do aluno que deseja consultar: ");
    scanf("%d", &matricula);
    Aluno aluno;
    int encontrado = 0;
    while (fread(&aluno, sizeof(Aluno), 1, file)) {
        if (aluno.matricula == matricula) {
            printf("Matricula: %d\n", aluno.matricula);
            printf("Nome: %s\n", aluno.nome);
            printf("Curso: %s\n", aluno.curso);
            printf("Idade: %d\n", aluno.idade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno não encontrado.\n");
    }
    fclose(file);
}
void listarAlunos() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Aluno aluno;
    printf("Lista de alunos cadastrados:\n");
    while (fread(&aluno, sizeof(Aluno), 1, file)) {
        printf("Matricula: %d\n", aluno.matricula);
        printf("Nome: %s\n", aluno.nome);
        printf("Curso: %s\n", aluno.curso);
        printf("Idade: %d\n\n", aluno.idade);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Incluir um novo aluno\n");
        printf("2. Alterar informações de um aluno\n");
        printf("3. Excluir um aluno\n");
        printf("4. Consultar informações de um aluno\n");
        printf("5. Listar todos os alunos\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                incluirAluno();
                break;
            case 2:
                alterarAluno();
                break;
            case 3:
                excluirAluno();
                break;
            case 4:
                consultarAluno();
                break;
            case 5:
                listarAlunos();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
