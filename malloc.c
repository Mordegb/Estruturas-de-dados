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

void salvarArquivos(){
    FILE *f = fopen ("amigos.bin" , "wb");
    if(f == NULL){
        printf("fudeu  em binario kkk");
        return ;
    }
    //escreve no arquivo
    fwrite(&qtd,sizeof(int), 1 , f);

    //escreve o vetor
    fwrite(vetor,sizeof(struct pessoa) , qtd , f);
    // ele escreve a quatidade de vezes de qtd, para não precisar usar loop

    fclose(f);
    printf("deu bom salvar em binario\n");
}

void carregarDados(){
    FILE *f = fopen ("amigos.bin" , "rb");
    if(f == NULL){
        FILE *f = fopen ("amigos.bin" , "wb");
    }

    //le a variavel de quantidade
    fread(&qtd,sizeof(int), 1 ,f);

    //le os arquivos e colocar no vetor
    fread(vetor,sizeof(struct pessoa) , qtd, f);
    fclose(f);
    printf("deu bom carregar");
}

//atualizar, função pra pegar nome e deixar em maiusculo.
char* maiusculo(char nome[]){
    nome[strcspn(nome, "\n")] = '\0';
    for(int i = 0; nome[i] != '\0'; i++){
        nome[i] = toupper(nome[i]);
    }
    return nome;
}

bool addPessoa(){
    if(qtd == max){
        return false;
    }
    struct pessoa pessoa;
    getchar();
    printf("Insira o nome: ");
    fgets(pessoa.nome,90,stdin);
    fflush(stdout);
    maiusculo(pessoa.nome);

    printf("Insira a idade: ");
    scanf("%d" , &pessoa.idade);

    getchar();
    printf("insira o bairro: ");
    fgets(pessoa.bairro,90,stdin);
    pessoa.bairro[strcspn(pessoa.bairro,"\n")] = '\0';
    //remove o \n

    vetor[qtd] = pessoa;
    qtd++;
    return true;

}

bool removerPessoa(){
    if(qtd == 0){
        printf("tem que adicionar pra remover");
        return false;
    }
    char nome[90];
    getchar();
    printf("insira o nome da pessoa que deseja remover: ");
    fgets(nome,90,stdin);
    fflush(stdout);
    maiusculo(nome);

    int indice = 101;
    for(int i = 0; i < qtd; i++){
        if(strcmp(vetor[i].nome,nome) == 0){
            indice = i;
            break;
        }
    }
    if(indice == 101){
        printf("nome não foi encontrado\n");
        return false;
    }

    for(int i = indice; i < qtd; i++){
        vetor[i] = vetor[i + 1];
    }
    qtd--;
    return true;

}


bool removerPessoaIndice() {
    //adicionar logica prqa procurar indice
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
        for (int i = indice; i < qtd; i++) {
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
            salvarArquivos();
            break;
            }

        case 2: {
            removerPessoa();
            salvarArquivos();
            break;
            }


        case 3: {
            removerPessoaIndice();
            salvarArquivos();
            break;
            }

        case 4: {
            listarpessoas();
            salvarArquivos();
            break;
        }

        case 5: {
            editarPessoa();
            salvarArquivos();
            break;
        }

    }

    return 0;
}
