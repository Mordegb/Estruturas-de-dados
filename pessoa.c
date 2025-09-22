#include <stdio.h>
#include <stdbool.h>
#define max 100
struct pessoa {
    char nome[50];
    int idade;
    char bairro[50];
};
struct pessoa vetor[max];
int qtd = 0;


void salvarDados() {
    FILE *f = fopen("amigos.txt", "w");
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
        fprintf(f,"%s\n" , vetor[i].bairro);
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
    //le a quantidade de pessoas
    fscanf(f,"%d\n" ,&qtd);

    //le o arquivo e colocar no array de struct correspondente
    for (int i = 0; i < qtd; i++) {
        fscanf(f,"%s\n" , vetor[i].nome);
        fscanf(f,"%d\n" , &vetor[i].idade);
        fscanf(f,"%s\n" , vetor[i].bairro);
    }
    fclose(f);
    printf("deu bom carregar");

}



bool addPessoa() {
    if(qtd == max){
        return false;
    }
    struct pessoa pessoa;
    printf("Insira o nome: \n");
    fgets(pessoa.nome,50,stdin);

    printf("Insira o idade: ");
    scanf("%d" , &pessoa.idade);

    printf("Insira o matricula: ");
    fgets(pessoa.bairro,50,stdin);

    vetor[qtd] = pessoa;
    qtd++;
    return true;
}

bool removerPessoaNome() {
    if(qtd == 0) {
        printf("tem que adicionar pra remover");
        return false;
    }
    char nome[50];
    printf("Insira o nome que deseja remover: ");
    fgets(nome, 50, stdin);

    int indice;
    for (int i = 0; i < qtd; i++) {
        if (vetor[i].nome == nome) {
            indice = i;
        }
    }
    for (int i = indice - 1; i < qtd; i++) {
        vetor[i] = vetor[ i + 1];
    }
    qtd--;
    return true;
}

bool removerPessoaIndice() {
    printf("diga o indice que deseja remover: ");
    int indice;
    scanf("%d" , &indice);

    printf("a seguinte pessoa ocupa esse indice do array: \n");
    printf("Nome: %s\n", vetor[indice].nome);
    printf("Nome: %d\n", vetor[indice].idade);
    printf("Nome: %s\n", vetor[indice].bairro);

    char res;
    printf("deseja mesmo remover a pessoa?");
    scanf("%s" , &res);
    if (res == 's') {
        for (int i = indice; i < qtd; i++) {
            vetor[i] = vetor[i + 1];
            qtd--;
        }
        return true;
    }
    else {
        return false;
    }

}



void listarpessoas() {
    printf("\n");
    for (int i = 0; i < qtd; i++) {
        printf("nome: %s\n" , vetor[i].nome);
        printf("idade: %d\n" , vetor[i].idade);
        printf("bairro: %s\n" , vetor[i].bairro);
    }
    printf("\n");
}




int main() {

    return 0;
}