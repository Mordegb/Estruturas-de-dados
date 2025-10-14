#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct trem{
    int NumVagao;
    char dica[50];
    struct trem *prox;
}trem;

void inicar(trem** head){
    *head = NULL;
    printf("numero iniciado com sucesso");
}

trem* criarVagão(int numero,const char* dica){
    trem* novoVagao = (trem*)malloc(sizeof(trem));
    if(novoVagao == NULL){
        printf("erro ao colocar memoria\n");
        return NULL;
    }
    novoVagao->NumVagao = numero;
    strcpy(novoVagao->dica,dica);
    novoVagao->prox = NULL;

    return novoVagao;
}

void adicionarVagaoNovo(trem** head,int numero,const char* dica){
    trem* NovoVagao = criarVagão(numero,dica) ;

    if(*head == NULL){
        //fudeu o negocio ta vazio, bota o novo na cabeça
        *head = NovoVagao;
    }
    else{
        trem* atual = *head;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        atual->prox = NovoVagao;
    }
    printf("vagão %d adicionado: %s\n", numero,dica);
}

void RemoverPorCodigo(trem** head , int codigo){
    if(*head == NULL){
        //adicione algo antes de remover né meu fi
        printf("trem vazio, nada a remover\n");
        return;
    }

    trem* atual = *head;
    trem* anterior = *head;

    while (atual != NULL && atual->NumVagao != codigo){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("pista não encontrada");
        return;
    }

    anterior->prox = atual->prox;
    printf("Pista %d removida: %s\n", atual->NumVagao, atual->dica);
    free(atual);
    
}

void MostrarTrem(trem* head){
    if(head == NULL){
        printf("trem vazio, coloque os vagões para olhar dentro");
        return;
    }
    trem* atual = head;
    int count = 1;

    printf("\n===Vagão do maquinista===\n");
    while(atual != NULL){
        printf("NUmero do vagão:[%d] dica:(%s)\n" , atual->NumVagao , atual->dica);
        atual = atual->prox;
        count++;
        if(atual == NULL){
            printf("==final do trem==");
        }
    }
    printf("========================\n\n");

}

void buscarPorCodigo(trem* head, int codigo){
    trem* atual = head;

    while(atual != NULL){
        if(atual->NumVagao == codigo){
            printf("vagão encontrado, dica: '%s'\n" , atual->dica);
            return;
        }
        atual = atual->prox;
    }
    printf("vagão não encontrado");
}

void ExplodirTrem(trem* head){
    trem* atual = head;
    trem* proxima;

    while(atual != NULL){
        proxima = atual->prox;
        free(atual);
        atual = proxima;
    }
}




int main(){
    trem* head; //declara o começo da lista
    inicar(&head);
    int opt;

    do{
        printf("=====Bem vindo ao acervo=====\n");
        printf("1 - adicionar vagão, 2 - remover vagão por codigo\n ");
        printf("3 - buscar por codigo , 4 listar livros\n");
        scanf("%d" , &opt);
        getchar();

        switch (opt)
        {
        case 1:{
            char dica[50];
            int numVagao;

            printf("diga o numero do vagão: ");
             scanf("%d" , &numVagao);
             getchar();
            printf("de uma dica: ");
            fgets(dica,50,stdin);
            fflush(stdout);
            dica[strcspn(dica, "\n")] = '\0';

            adicionarVagaoNovo(&head,numVagao,dica);
            break;
        }

        case 2:{
            int numVagao;
            printf("digite o numero do vagão que deseja buscar: ");
            scanf("%d" , &numVagao);

            RemoverPorCodigo(&head , numVagao);
            break;
        }

        case 3:{
             int numVagao;
            printf("digite o numero do vagão que deseja buscar: ");
            scanf("%d" , &numVagao);

            buscarPorCodigo(head , numVagao);
            break;
        }

        case 4:{
            MostrarTrem(head);
            break;
        }
        
        default:
            break;
        }

    }while(opt > 0 && opt < 5 );

    ExplodirTrem(head);


    return 0;
}