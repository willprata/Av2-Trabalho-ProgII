#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "acervo_filmes.dat"
typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;
void adicionarFilme() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Filme filme;
    printf("Digite o ID do filme: ");
    scanf("%d", &filme.id);
    getchar(); 
    printf("Digite o título do filme: ");
    fgets(filme.titulo, sizeof(filme.titulo), stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = '\0';  
    printf("Digite o gênero do filme: ");
    fgets(filme.genero, sizeof(filme.genero), stdin);
    filme.genero[strcspn(filme.genero, "\n")] = '\0'; 
    printf("Digite o ano de lançamento do filme: ");
    scanf("%d", &filme.ano);
    fwrite(&filme, sizeof(Filme), 1, file);
    fclose(file);
    printf("Filme adicionado ao acervo com sucesso!\n");
}
void alterarFilme() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int id;
    printf("Digite o ID do filme que deseja alterar: ");
    scanf("%d", &id);
    Filme filme;
    int encontrado = 0;
    while (fread(&filme, sizeof(Filme), 1, file)) {
        if (filme.id == id) {
            printf("Filme encontrado! \n");
            printf("Novo título: ");
            getchar(); 
            fgets(filme.titulo, sizeof(filme.titulo), stdin);
            filme.titulo[strcspn(filme.titulo, "\n")] = '\0';
            printf("Novo gênero: ");
            fgets(filme.genero, sizeof(filme.genero), stdin);
            filme.genero[strcspn(filme.genero, "\n")] = '\0';
            printf("Novo ano de lançamento: ");
            scanf("%d", &filme.ano);
            fseek(file, -sizeof(Filme), SEEK_CUR); 
            fwrite(&filme, sizeof(Filme), 1, file);
            printf("Dados do filme atualizados com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }
    fclose(file);
}
void excluirFilme() {
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
    printf("Digite o ID do filme que deseja excluir: ");
    scanf("%d", &id);
    Filme filme;
    int encontrado = 0;
    while (fread(&filme, sizeof(Filme), 1, file)) {
        if (filme.id != id) {
            fwrite(&filme, sizeof(Filme), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(file);
    fclose(temp);
    if (encontrado) {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Filme excluído com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("Filme não encontrado.\n");
    }
}
void consultarFilme() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int id;
    printf("Digite o ID do filme que deseja consultar: ");
    scanf("%d", &id);
    Filme filme;
    int encontrado = 0;
    while (fread(&filme, sizeof(Filme), 1, file)) {
        if (filme.id == id) {
            printf("ID: %d\n", filme.id);
            printf("Título: %s\n", filme.titulo);
            printf("Gênero: %s\n", filme.genero);
            printf("Ano de lançamento: %d\n", filme.ano);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Filme não encontrado.\n");
    }
    fclose(file);
}
void listarFilmes() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Filme filme;
    printf("Lista de filmes cadastrados:\n");
    while (fread(&filme, sizeof(Filme), 1, file)) {
        printf("ID: %d\n", filme.id);
        printf("Título: %s\n", filme.titulo);
        printf("Gênero: %s\n", filme.genero);
        printf("Ano de lançamento: %d\n\n", filme.ano);
    }
    fclose(file);
}
int main() {
    int opcao;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Adicionar um novo filme\n");
        printf("2. Alterar dados de um filme\n");
        printf("3. Excluir um filme\n");
        printf("4. Consultar informações de um filme\n");
        printf("5. Listar todos os filmes\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionarFilme();
                break;
            case 2:
                alterarFilme();
                break;
            case 3:
                excluirFilme();
                break;
            case 4:
                consultarFilme();
                break;
            case 5:
                listarFilmes();
                break;
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
