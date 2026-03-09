#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nome[51];
    int pontos;
} jogador;

typedef struct No
{
    jogador jogador;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

int altura(No *n)
{
    return (n == NULL) ? 0 : n->altura;
}

int max(int n1, int n2)
{
    return (n1 > n2) ? n1 : n2;
}

No *novoNo(int id, char *nome, int pontos)
{
    No *no = (No *)malloc(sizeof(No));
    no->jogador.id = id;
    strncpy(no->jogador.nome, nome, 50);
    no->jogador.nome[30] = '\0';
    no->jogador.pontos = pontos;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

No *rotacaoEsquerda(No *y)
{
    No *x = y->direita;
    No *T2 = x->esquerda;

    x->esquerda = y;
    y->direita = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    return x;
}

No *rotacaoDireita(No *y)
{
    No *x = y->esquerda;
    No *T2 = x->direita; // O "filho da direita do filho da esquerda"

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

int getBalanceamento(No *n)
{
    return (n == NULL) ? 0 : altura(n->esquerda) - altura(n->direita);
}

int compararJogadores(int p1, int id1, int p2, int id2)
{
    if (p1 < p2)
        return -1;
    if (p1 > p2)
        return 1;
    // Se pontos iguais, ID menor fica à esquerda
    if (id1 < id2)
        return -1;
    if (id1 > id2)
        return 1;
    return 0;
}

No *inserir(No *no, int id, char *nome, int pontos)
{
    if (no == NULL)
        return novoNo(id, nome, pontos);

    int cmp = compararJogadores(pontos, id, no->jogador.pontos, no->jogador.id);

    if (cmp < 0)
        no->esquerda = inserir(no->esquerda, id, nome, pontos);
    else if (cmp > 0)
        no->direita = inserir(no->direita, id, nome, pontos);
    else
        return no;

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int balance = getBalanceamento(no);

    if (balance > 1 && compararJogadores(pontos, id, no->esquerda->jogador.pontos, no->esquerda->jogador.id) < 0)
        return rotacaoDireita(no);

    if (balance < -1 && compararJogadores(pontos, id, no->direita->jogador.pontos, no->direita->jogador.id) > 0)
        return rotacaoEsquerda(no);

    if (balance > 1 && compararJogadores(pontos, id, no->esquerda->jogador.pontos, no->esquerda->jogador.id) > 0)
    {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balance < -1 && compararJogadores(pontos, id, no->direita->jogador.pontos, no->direita->jogador.id) < 0)
    {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

No *buscarPorID(No *raiz, int id)
{
    if (raiz == NULL || raiz->jogador.id == id)
        return raiz;
    No *esq = buscarPorID(raiz->esquerda, id);
    return (esq != NULL) ? esq : buscarPorID(raiz->direita, id);
}

No *noValorMinimo(No *node)
{
    No *current = node;
    while (current->esquerda != NULL)
        current = current->esquerda;
    return current;
}

No *removerNoLogica(No *raiz, int pontos, int id)
{
    if (raiz == NULL)
        return raiz;
    int cmp = compararJogadores(pontos, id, raiz->jogador.pontos, raiz->jogador.id);

    if (cmp < 0)
        raiz->esquerda = removerNoLogica(raiz->esquerda, pontos, id);
    else if (cmp > 0)
        raiz->direita = removerNoLogica(raiz->direita, pontos, id);
    else
    {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL))
        {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
                *raiz = *temp;
            free(temp);
        }
        else
        {
            No *temp = noValorMinimo(raiz->direita);
            raiz->jogador = temp->jogador;
            raiz->direita = removerNoLogica(raiz->direita, temp->jogador.pontos, temp->jogador.id);
        }
    }
    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));
    int balance = getBalanceamento(raiz);
    if (balance > 1 && getBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);
    if (balance > 1 && getBalanceamento(raiz->esquerda) < 0)
    {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    if (balance < -1 && getBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);
    if (balance < -1 && getBalanceamento(raiz->direita) > 0)
    {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}

int contarJogadores(No *raiz)
{
    return (raiz == NULL) ? 0 : 1 + contarJogadores(raiz->esquerda) + contarJogadores(raiz->direita);
}

void preOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        printf("[%d] %s (%d pts) | ", raiz->jogador.id, raiz->jogador.nome, raiz->jogador.pontos);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esquerda);
        printf("[%d] %s (%d pts) | ", raiz->jogador.id, raiz->jogador.nome, raiz->jogador.pontos);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("[%d] %s (%d pts) | ", raiz->jogador.id, raiz->jogador.nome, raiz->jogador.pontos);
    }
}

void exibirTop3(No *raiz, int *caunt)
{
    if (raiz != NULL && *caunt < 3)
    {
        exibirTop3(raiz->direita, caunt);
        if (*caunt < 3)
        {
            printf("%d. %s - %d pontos\n", *caunt + 1, raiz->jogador.nome, raiz->jogador.pontos);
            (*caunt)++;
        }
        exibirTop3(raiz->esquerda, caunt);
    }
}

void desenharArvore(No *raiz, int nivel)
{
    if (raiz == NULL)
        return;
    desenharArvore(raiz->direita, nivel + 1);
    for (int i = 0; i < nivel; i++)
        printf("      ");
    printf("|-- %d\n", raiz->jogador.pontos);
    desenharArvore(raiz->esquerda, nivel + 1);
}

int main()
{
    No *raiz = NULL;
    int opcao, id, pontos, count;
    char nome[31];

    do
    {
        printf("\n======= SISTEMA DE RANKING (AVL) =======\n");
        printf("1. inserir jogador\n");
        printf("2. buscar por ID\n");
        printf("3. atualizar pontuacao\n");
        printf("4. ver total de jogadores\n");
        printf("5. remover por ID\n");
        printf("6. remover menor pontuacao\n");
        printf("7. exibir rankings (Pre/Em/Pos)\n");
        printf("8. ver TOP 3 (Premiados)\n");
        printf("9. ver estrutura da arvore\n");
        printf("0. sair\n");
        printf(">>: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("ID, Nome, Pontos: ");
            scanf("%d %s %d", &id, nome, &pontos);
            if (buscarPorID(raiz, id))
                printf("Erro: ID ja existe!\n");
            else
                raiz = inserir(raiz, id, nome, pontos);
            break;
        case 2:
            printf("ID para busca: ");
            scanf("%d", &id);
            No *b = buscarPorID(raiz, id);
            if (b)
                printf("achado: %s (%d pts)\n", b->jogador.nome, b->jogador.pontos);
            else
                printf("nao encontrado.\n");
            break;
        case 3:
            printf("ID e nova pontuacao: ");
            scanf("%d %d", &id, &pontos);
            No *alvo = buscarPorID(raiz, id);
            if (alvo)
            {
                strcpy(nome, alvo->jogador.nome);
                raiz = removerNoLogica(raiz, alvo->jogador.pontos, id);
                raiz = inserir(raiz, id, nome, pontos);
                printf("atualizado!\n");
            }
            else
                printf("ID nao existe.\n");
            break;
        case 4:
            printf("Total: %d jogadores\n", contarJogadores(raiz));
            break;
        case 5:
            printf("ID para remover: ");
            scanf("%d", &id);
            No *r = buscarPorID(raiz, id);
            if (r)
                raiz = removerNoLogica(raiz, r->jogador.pontos, id);
            else
                printf("nao encontrado.\n");
            break;
        case 6:
            if (raiz != NULL)
            {
                No *menor = noValorMinimo(raiz);
                printf("removendo: %s (%d pts)\n", menor->jogador.nome, menor->jogador.pontos);

                raiz = removerNoLogica(raiz, menor->jogador.pontos, menor->jogador.id);
            }
            else
            {
                printf("a arvore ja esta vazia!\n");
            }
            break;
        case 7:
            printf("\nPre-ordem: ");
            preOrdem(raiz);
            printf("\nEm-ordem:  ");
            emOrdem(raiz);
            printf("\nPos-ordem: ");
            posOrdem(raiz);
            printf("\n");
            break;
        case 8:
            count = 0;
            printf("\n--- TOP 3 ---\n");
            exibirTop3(raiz, &count);
            break;
        case 9:
            printf("\n--- Estrutura da Arvore (90 graus) ---\n");
            desenharArvore(raiz, 0);
            break;
        }
    } while (opcao != 0);

    return 0;
}