#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define max 100
struct pessoa {
    char nome[90];
    int idade;
    char bairro[90];
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
    printf("deu bom salvar\n");
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
        fscanf(f,"%s\n" , &vetor[i].bairro);
    }
    fclose(f);
    printf("deu bom carregar");

}



bool addPessoa() {
    if(qtd == max){
        return false;
    }
    struct pessoa pessoa;
    getchar();
    printf("Insira o nome: ");
    fgets(pessoa.nome,90,stdin);
    //remove o \n
    pessoa.nome[strcspn(pessoa.nome, "\n")] = '\0';

    //deixa o nome em maiusculo
    for (int i = 0; pessoa.nome[i] != '\0'; i++) {
        pessoa.nome[i] = toupper(pessoa.nome[i]);
    }

    printf("Insira o idade: ");
    scanf("%d" , &pessoa.idade);

    getchar();
    printf("Insira o bairro: ");
    fgets(pessoa.bairro,90,stdin);
    pessoa.bairro[strcspn(pessoa.bairro, "\n")] = '\0';
    //remove o \n

    vetor[qtd] = pessoa;
    qtd++;
    return true;
}

bool removerPessoaNome() {
    if(qtd == 0) {
        printf("tem que adicionar pra remover");
        return false;
    }
    char nome[90];
    getchar();
    printf("Insira o nome que deseja remover: ");
    fgets(nome, 90, stdin);

    //verifica se algum nome foi digitado
    if (nome[0] == '\n' || nome[0] == '\0') {
        printf("Nenhum nome foi inserido!\n");
        return false;
    }

    //tira o \n
    nome[strcspn(nome, "\n")] = '\0';

    //deixa o nome em maiusculo
    for (int i = 0; nome[i] != '\0'; i++) {
        nome[i] = toupper(nome[i]);
    }

    int indice = 0;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(vetor[i].nome,nome) == 0){
            indice = i;
            break;
        }
    }
    if (indice == 0) {
        printf("nome não foi encontrado\n");
        return false;
    }

    for (int i = indice; i < qtd - 1; i++) {
        vetor[i] = vetor[ i + 1];
    }
    qtd--;
    return true;
}


bool removerPessoaIndice() {
    printf("diga o indice que deseja remover (0 a %d): ", qtd-1 );
    int indice;
    scanf("%d" , &indice);
    getchar();

    if (indice < 0 || indice >= qtd) {
        printf("esse indice não pode\n");
        return false;
    }

    printf("a seguinte pessoa ocupa esse indice do array: \n");
    printf("nome: %s\n", vetor[indice].nome);
    printf("idade: %d\n", vetor[indice].idade);
    printf("bairro: %s\n\n", vetor[indice].bairro);

    char res;
    printf("deseja mesmo remover a pessoa?\n");
    scanf("%c" , &res);
    if (res == 's' || res == 'S') {
        for (int i = indice; i < qtd - 1; i++) {
            vetor[i] = vetor[i + 1];
        }
        qtd--;
        return true;
    }
    else {
        return false;
    }

}

bool editarPessoa(){
    int indice;
    
    printf("diga o indice da pessoa que deseja editar: ");
     scanf("%d" , &indice);
    
     if(indice > qtd){
        return false;
    }

    printf("NOME: %s\n",vetor[indice].nome);
    printf("IDADE: %d\n",vetor[indice].idade);
    printf("BAIRRO: %s\n\n",vetor[indice].bairro);
    struct pessoa novo;

    getchar();
    printf("Novo nome: ");
    fgets(novo.nome,90,stdin);
    //remove o \n
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    //deixa o nome em maiusculo
    for (int i = 0; novo.nome[i] != '\0'; i++) {
        novo.nome[i] = toupper(novo.nome[i]);
    }
    printf("nova idade: ");
     scanf("%d", &novo.idade);
   
    getchar();
    printf("novo endereço: ");
     fgets(novo.bairro,90,stdin);
    //remove o \n
    novo.bairro[strcspn(novo.bairro, "\n")] = '\0';
    
    vetor[indice] = novo;
    return true;
}


void listarpessoas() {
    printf("\n");
    for (int i = 0; i < qtd; i++) {
        printf("nome: %s\n" , vetor[i].nome);
        printf("idade: %d\n" , vetor[i].idade);
        printf("bairro: %s\n" , vetor[i].bairro);
        printf("\n");
    }
    printf("quantidade de pessoas: %d" , qtd);
    printf("\n");
}


int main() {
    carregarDados();
    printf("\n\n");
      int opt;
    printf("1 - inserir pessoa.      2 - excluir por nome.\n");
    printf("3 - excluir por indice.     4 - listar pessoas.\n");
    printf("5 - editar pessoa.\n");
    scanf("%d", &opt);

    switch (opt) {
        case 1: {
            addPessoa();
            salvarDados();
            break;
            }

        case 2: {
            removerPessoaNome();
            salvarDados();
            break;
            }


        case 3: {
            removerPessoaIndice();
            salvarDados();
            break;
            }

        case 4: {
            listarpessoas();
            salvarDados();
            break;
        }

        case 5: {
            editarPessoa();
            salvarDados();
            break;
        }

    }

    return 0;
}