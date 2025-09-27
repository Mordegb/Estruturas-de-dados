#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define arquivo "livros.txt"
struct livro {
    char nome[50];
    int codigo;
};
struct livro livros[10];
int qtd = 0;

void salvarDados() {
    FILE *f = fopen(arquivo, "wii");
    if (f == NULL) {
        printf("fudeu meu fi");
        return;
    }

    fprintf(f,"%d\n" ,qtd);

    for (int i = 0; i < qtd; i++) {
        fprintf(f,"%s\n" ,livros[i].nome);
        fprintf(f,"%d\n" ,livros[i].codigo);
    }
    fclose(f);
    printf("deu bom salvar");
}

void lerArquivo() {
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("arquivo não criado ainda");
        return;
    }
    fscanf(f,"%d" , &qtd);
    for (int i = 0; i < qtd; i++) {
        fscanf(f,"%s" , &livros[i].nome);
        fscanf(f,"%d" , &livros[i].codigo);
    }
    fclose(f);
}

bool adicionarLivro() {
    if (qtd == 10) {
        printf("estoque cheio, não pode adicionar");
        return false;
    }

    struct livro liv;
    getchar();
    printf("Digite o nome do livro:\n");
    fflush(stdin);
    fgets(liv.nome, sizeof(liv.nome), stdin);
    printf("Digite o codigo do livro:\n");
    scanf("%d" , &liv.codigo);
    liv.nome[strcspn(liv.nome, "\n")] = '\0';

    livros[qtd] = liv;
    //deixa os nomes maiuculos
    for (int i = 0; liv.nome[i] != '\0'; i++) {
        liv.nome[i] = toupper(liv.nome[i]);
    }
    livros[qtd] = liv;
    qtd++;
    return true;
    salvarDados();
}

void listarLivros() {
    for (int i = 0; i < qtd; i++) {
        printf("Nome: %s\n" , livros[i].nome);
        printf("codigo: %d\n",livros[i].codigo);
        printf("\n");
    }
}

void buscar() {
    int code;
    printf("Digite o codigo que deseja buscar:\n");
    scanf("%d" , &code);
    for (int i = 0; i < qtd; i++) {
        if (code == livros[i].codigo) {
            printf("===LIVRO ACHADO===\n");
            printf("Nome: %s\n" , livros[i].nome);
            printf("Codigo: %d\n",livros[i].codigo);
        }
    }
}


bool removerLivro() {
    if (qtd == 0) {
        printf("adicione algo para poder remover");
        return false;
    }
    listarLivros();
    printf("digite o codigo do livro que deseja remover: ");
    int codigo;
    scanf("%d" , &codigo);

    for (int i = 0; i < qtd; i++) {
        if (codigo == livros[i].codigo) {
            livros[i] = livros[i + 1];
        }
    }
    qtd--;
    return true;
}

int main() {
    lerArquivo();

    int opt;
    printf("=====Bem vindo ao acervo=====\n");
    printf("1 - adicionar livro, 2 - remover livro ");
    printf("3 - buscar livros , 4 listar livros\n");
    scanf("%d" , &opt);

    switch (opt) {
        case 1:
            adicionarLivro();
            salvarDados();
            break;

        case 2:
            removerLivro();
            salvarDados();
            break;

        case 3:
            buscar();
            salvarDados();
            break;

        case 4:
            listarLivros();
            break;
    }


    return 0;
}

