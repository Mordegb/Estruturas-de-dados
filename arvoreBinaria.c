#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char nome[31];
    int pontos;
} Jogador;

typedef struct No {
    Jogador jogador;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;


int altura(No *N) {
    return (N == NULL) ? 0 : N->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

No* novoNo(int id, char* nome, int pontos) {
    No* no = (No*)malloc(sizeof(No));
    no->jogador.id = id;
    strncpy(no->jogador.nome, nome, 30);
    no->jogador.nome[30] = '\0';
    no->jogador.pontos = pontos;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    return x;
}

No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    return y;
}

int getBalanceamento(No *N) {
    return (N == NULL) ? 0 : altura(N->esquerda) - altura(N->direita);
}

int compararJogadores(int pts1, int id1, int pts2, int id2) {
    if (pts1 != pts2) return pts1 - pts2;
    return id1 - id2;
}

// --- Funcionalidades do Sistema ---

No* inserir(No* no, int id, char* nome, int pontos) {
    if (no == NULL) return novoNo(id, nome, pontos);

    int cmp = compararJogadores(pontos, id, no->jogador.pontos, no->jogador.id);
    if (cmp < 0) no->esquerda = inserir(no->esquerda, id, nome, pontos);
    else if (cmp > 0) no->direita = inserir(no->direita, id, nome, pontos);
    else return no;

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    int balance = getBalanceamento(no);

    if (balance > 1 && compararJogadores(pontos, id, no->esquerda->jogador.pontos, no->esquerda->jogador.id) < 0)
        return rotacaoDireita(no);
    if (balance < -1 && compararJogadores(pontos, id, no->direita->jogador.pontos, no->direita->jogador.id) > 0)
        return rotacaoEsquerda(no);
    if (balance > 1 && compararJogadores(pontos, id, no->esquerda->jogador.pontos, no->esquerda->jogador.id) > 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (balance < -1 && compararJogadores(pontos, id, no->direita->jogador.pontos, no->direita->jogador.id) < 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no;
}

No* buscarPorID(No* root, int id) {
    if (root == NULL || root->jogador.id == id) return root;
    No* esq = buscarPorID(root->esquerda, id);
    return (esq != NULL) ? esq : buscarPorID(root->direita, id);
}

No *noValorMinimo(No* node) {
    No* current = node;
    while (current->esquerda != NULL) current = current->esquerda;
    return current;
}

No* removerNoLogica(No* root, int pontos, int id) {
    if (root == NULL) return root;
    int cmp = compararJogadores(pontos, id, root->jogador.pontos, root->jogador.id);

    if (cmp < 0) root->esquerda = removerNoLogica(root->esquerda, pontos, id);
    else if (cmp > 0) root->direita = removerNoLogica(root->direita, pontos, id);
    else {
        if ((root->esquerda == NULL) || (root->direita == NULL)) {
            No *temp = root->esquerda ? root->esquerda : root->direita;
            if (temp == NULL) { temp = root; root = NULL; }
            else *root = *temp;
            free(temp);
        } else {
            No* temp = noValorMinimo(root->direita);
            root->jogador = temp->jogador;
            root->direita = removerNoLogica(root->direita, temp->jogador.pontos, temp->jogador.id);
        }
    }
    if (root == NULL) return root;

    root->altura = 1 + max(altura(root->esquerda), altura(root->direita));
    int balance = getBalanceamento(root);
    if (balance > 1 && getBalanceamento(root->esquerda) >= 0) return rotacaoDireita(root);
    if (balance > 1 && getBalanceamento(root->esquerda) < 0) {
        root->esquerda = rotacaoEsquerda(root->esquerda);
        return rotacaoDireita(root);
    }
    if (balance < -1 && getBalanceamento(root->direita) <= 0) return rotacaoEsquerda(root);
    if (balance < -1 && getBalanceamento(root->direita) > 0) {
        root->direita = rotacaoDireita(root->direita);
        return rotacaoEsquerda(root);
    }
    return root;
}

int contarJogadores(No* root) {
    return (root == NULL) ? 0 : 1 + contarJogadores(root->esquerda) + contarJogadores(root->direita);
}

void preOrdem(No *root) {
    if (root != NULL) {
        printf("[%d] %s (%d pts) | ", root->jogador.id, root->jogador.nome, root->jogador.pontos);
        preOrdem(root->esquerda);
        preOrdem(root->direita);
    }
}

void emOrdem(No *root) {
    if (root != NULL) {
        emOrdem(root->esquerda);
        printf("[%d] %s (%d pts) | ", root->jogador.id, root->jogador.nome, root->jogador.pontos);
        emOrdem(root->direita);
    }
}

void posOrdem(No *root) {
    if (root != NULL) {
        posOrdem(root->esquerda);
        posOrdem(root->direita);
        printf("[%d] %s (%d pts) | ", root->jogador.id, root->jogador.nome, root->jogador.pontos);
    }
}

void exibirTop3(No* root, int* contador) {
    if (root != NULL && *contador < 3) {
        exibirTop3(root->direita, contador);
        if (*contador < 3) {
            printf("%d. %s - %d pontos\n", *contador + 1, root->jogador.nome, root->jogador.pontos);
            (*contador)++;
        }
        exibirTop3(root->esquerda, contador);
    }
}

// Função para desenhar a árvore (Visualização técnica)
void desenharArvore(No *root, int nivel) {
    if (root == NULL) return;
    desenharArvore(root->direita, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("      ");
    printf("|-- %d\n", root->jogador.pontos);
    desenharArvore(root->esquerda, nivel + 1);
}

// --- Menu de Usuário ---

int main() {
    No *raiz = NULL;
    int opcao, id, pontos, count;
    char nome[31];

    do {
        printf("\n======= SISTEMA DE RANKING (AVL) =======\n");
        printf("1. Inserir Jogador\n");
        printf("2. Buscar por ID\n");
        printf("3. Atualizar Pontuacao\n");
        printf("4. Ver Total de Jogadores\n");
        printf("5. Remover por ID\n");
        printf("6. Remover Menor Pontuacao\n");
        printf("7. Exibir Rankings (Pre/Em/Pos)\n");
        printf("8. Ver TOP 3 (Premiados)\n");
        printf("9. Ver Estrutura da Arvore\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("ID, Nome, Pontos: ");
                scanf("%d %s %d", &id, nome, &pontos);
                if (buscarPorID(raiz, id)) printf("Erro: ID ja existe!\n");
                else raiz = inserir(raiz, id, nome, pontos);
                break;
            case 2:
                printf("ID para busca: ");
                scanf("%d", &id);
                No* b = buscarPorID(raiz, id);
                if(b) printf("Achado: %s (%d pts)\n", b->jogador.nome, b->jogador.pontos);
                else printf("Nao encontrado.\n");
                break;
            case 3:
                printf("ID e Nova Pontuacao: ");
                scanf("%d %d", &id, &pontos);
                No* alvo = buscarPorID(raiz, id);
                if(alvo) {
                    strcpy(nome, alvo->jogador.nome);
                    raiz = removerNoLogica(raiz, alvo->jogador.pontos, id);
                    raiz = inserir(raiz, id, nome, pontos);
                    printf("Atualizado!\n");
                } else printf("ID nao existe.\n");
                break;
            case 4:
                printf("Total: %d jogadores\n", contarJogadores(raiz));
                break;
            case 5:
                printf("ID para remover: ");
                scanf("%d", &id);
                No* r = buscarPorID(raiz, id);
                if(r) raiz = removerNoLogica(raiz, r->jogador.pontos, id);
                else printf("Nao encontrado.\n");
                break;
            case 6:
                if(raiz != NULL){
                    No* menor = noValorMinimo(raiz);
                    printf("Removendo: %s (%d pts)\n", menor->jogador.nome, menor->jogador.pontos);
                    
                    raiz = removerNoLogica(raiz, menor->jogador.pontos, menor->jogador.id);
                } else {
                    printf("A arvore ja esta vazia!\n");
                }
                break;
            case 7:
                printf("\nPre-Ordem: "); preOrdem(raiz);
                printf("\nEm-Ordem:  "); emOrdem(raiz);
                printf("\nPos-Ordem: "); posOrdem(raiz);
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
    } while(opcao != 0);

    return 0;
}