#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "catalogo_livros.dat"
typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;
void adicionarLivro() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Livro livro;
    printf("Digite o código do livro: ");
    scanf("%d", &livro.codigo);
    getchar(); 
    printf("Digite o título do livro: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0';  
    printf("Digite o autor do livro: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0';
    printf("Digite o ano de publicação do livro: ");
    scanf("%d", &livro.ano);
    fwrite(&livro, sizeof(Livro), 1, file);
    fclose(file);
    printf("Livro adicionado com sucesso!\n");
}
void alterarLivro() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int codigo;
    printf("Digite o código do livro que deseja alterar: ");
    scanf("%d", &codigo);
    Livro livro;
    int encontrado = 0;
    while (fread(&livro, sizeof(Livro), 1, file)) {
        if (livro.codigo == codigo) {
            printf("Livro encontrado! \n");
            printf("Novo título: ");
            getchar(); 
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = '\0';
            printf("Novo autor: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            livro.autor[strcspn(livro.autor, "\n")] = '\0';
            printf("Novo ano de publicação: ");
            scanf("%d", &livro.ano);
            fseek(file, -sizeof(Livro), SEEK_CUR); 
            fwrite(&livro, sizeof(Livro), 1, file);
            printf("Dados do livro atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
    fclose(file);
}
void excluirLivro() {
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
    int codigo;
    printf("Digite o código do livro que deseja excluir: ");
    scanf("%d", &codigo);
    Livro livro;
    int encontrado = 0;
    while (fread(&livro, sizeof(Livro), 1, file)) {
        if (livro.codigo != codigo) {
            fwrite(&livro, sizeof(Livro), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Livro excluído com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("Livro não encontrado.\n");
    }
}
void consultarLivro() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int codigo;
    printf("Digite o código do livro que deseja consultar: ");
    scanf("%d", &codigo);
    Livro livro;
    int encontrado = 0;
    while (fread(&livro, sizeof(Livro), 1, file)) {
        if (livro.codigo == codigo) {
            printf("Código: %d\n", livro.codigo);
            printf("Título: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano de publicação: %d\n", livro.ano);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Livro não encontrado.\n");
    }
    fclose(file);
}
void listarLivros() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Livro livro;
    printf("Lista de livros cadastrados:\n");
    while (fread(&livro, sizeof(Livro), 1, file)) {
        printf("Código: %d\n", livro.codigo);
        printf("Título: %s\n", livro.titulo);
        printf("Autor: %s\n", livro.autor);
        printf("Ano de publicação: %d\n\n", livro.ano);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar um novo livro\n");
        printf("2. Alterar dados de um livro\n");
        printf("3. Excluir um livro\n");
        printf("4. Consultar informações de um livro\n");
        printf("5. Listar todos os livros\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                alterarLivro();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                consultarLivro();
                break;
            case 5:
                listarLivros();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
