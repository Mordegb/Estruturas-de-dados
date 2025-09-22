#include <stdio.h>
#include <stdbool.h>
struct pessoa {
    char nome[50];
    int idade;
    int matricula;
};
#define max 100
struct pessoa vetor[max];
int qtd = 0;

void salvarDados() {
    FILE *f = fopen("pessoas.txt", "w");
    if (f == NULL) {
        printf("fudeu meu fi");
        return;
    }
    //escrever a quantidade de pessoas
    fprintf(f,"%d\n" ,qtd);

    //escreve a quantidade de pessoas
    for (int i = 0; i < qtd; i++) {
        fprintf(f,"%s\n" , vetor[i].nome);
        fprintf(f,"%d\n" , vetor[i].idade);
        fprintf(f,"%d\n" , vetor[i].matricula);
        printf("\n");
    }
    fclose(f);
    printf("deu bom salvar");
}

void carregarDados() {
    FILE *f = fopen("amigos.txt", "r");
    if (f == NULL) {
        printf("fudeu meu fi");
        return;
    }

    fscanf(f,"%d\n" ,&qtd);

    for (int i = 0; i < qtd; i++) {
        fscanf(f,"%s\n" , vetor[i].nome);
        fscanf(f,"%d\n" , &vetor[i].idade);
        fscanf(f,"%d\n" , &vetor[i].matricula);
    }
    fclose(f);
    printf("deu bom carregar");

}

bool add_pessoa() {
    if(qtd == max){
        return false;
    }
    struct pessoa pessoa;
    printf("Insira o nome:" "\n");
    scanf("%s" , &pessoa.nome);
    printf("Insira o idade:" "\n");
    scanf("%d" , &pessoa.idade);
    printf("Insira o matricula:" "\n");
    scanf("%d" , &pessoa.matricula);
    vetor[qtd] = pessoa;
    qtd++;
    return true;
}

void listarpessoas() {
    printf("\n");
    for (int i = 0; i < qtd; i++) {
        printf("nome: %s\n" , vetor[i].nome);
        printf("idade: %d\n" , vetor[i].idade);
        printf("matricula: %d\n" , vetor[i].matricula);
    }
    printf("\n");
}




int main() {
carregarDados();

    int opcao;
    scanf("%d" , &opcao);
    if (opcao == 1) {
        add_pessoa();
        salvarDados();
    }
    else {
    listarpessoas();
    }


    return 0;
}