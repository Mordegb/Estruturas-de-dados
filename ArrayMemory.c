#include <stdio.h>
#include <stdbool.h>
#define MAX 100
#define ARQUIVO "dados_array.txt"
int qtd = 0;
int vetor[MAX];

//retorna a quantidade de elementos no vetor
int tamanho() {
    return qtd;
}

void salvarDados() {
    //salva os dados para o arquivo de texto
    FILE *file = fopen(ARQUIVO, "w");
    if (file == NULL) {
        printf("erro pra criar arquivo\n");
        return;
    }

    // escreve a quantidade de valores no arquivo
    fprintf(file, "%d\n", qtd);

    // escrever cada valor no arquivo
    for (int i = 0; i < qtd; i++) {
        fprintf(file, "%d\n", vetor[i]);
    }

    fclose(file);
    printf("deu bom salvar os dados\n");
}

// função para carregar os dados do arquivo
void carregarDados() {
    FILE *file = fopen(ARQUIVO, "r");
    if (file == NULL) {
        printf("arquivo não encontrado, iniciando um array vazio.(deu ruim) \n");
        return;
    }

    // Le a quantidade de valores no arquivo
    fscanf(file, "%d", &qtd);

    // Lê os os elementos
    for (int i = 0; i < qtd; i++) {
        fscanf(file, "%d", &vetor[i]);
    }

    fclose(file);
    printf("Dados carregados com sucesso!\n");
}

//insere um valor numa posição especifica do array
bool inserirPosicao(int posi,int valor) {

    if (qtd == MAX || posi < 0 || posi > qtd) {
        return false;
    }
    //move todos os numeros a partir da posição para a direita;
    for (int i = qtd; i > posi; i--) {
        vetor[i] = vetor[i - 1];
    }
    vetor[posi] = valor;
    qtd++;
    return true;
}

bool inserirFinal(int valor) { //insere um valor no final do array
    if (qtd == MAX) {
        return false; //vetor ta cheio
    }
    vetor[qtd] = valor;
    qtd++;
    return true;
}

bool removerPosicao(int posi) {
    if (posi < 0 || posi >= qtd) {
        return false;
    }
    //move todos os valores a partir da posição pra esquerda
    for (int i = posi; i < qtd - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    qtd--;
    return true;
}

bool removerValor(int valor) {
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] == valor) {
            return removerPosicao(i);
        }
    }
    return false;
}

int buscarValor(int valor) {
    for (int i = 0; i < qtd; i++) {
        if (vetor[i] == valor) {
            return i;
        }
    }
    return -1;
}

void imprimirVetor() {
    printf("[");
    for (int i = 0; i < qtd; i++) {
        printf("%d ", vetor[i]);
    }
    printf("]\nQuantidade: %d\n\n", qtd);
}

int main(){
    // Carrega os dados ao iniciar o programa
    carregarDados();

    int opt;

    printf("\nDigite um numero de acordo com a opção:\n");
    printf("1 - inserir em posição.  2 - inserir no final.\n");
    printf("3 - excluir posição.     4 - remover valor.\n");
    printf("5 - buscar valor.        6 - imprimir array.\n");
    printf("Opção: ");
    scanf("%d", &opt);

    switch (opt) {
        case 1: {
            int valor, pos;
            printf("Digite um valor para inserir no array: ");
            scanf("%d", &valor);
            printf("colocar o valor %d em qual posição do array: " , valor);
            scanf("%d", &pos);
            if (inserirPosicao(pos, valor)) {
                printf("Valor %d inserido na posição %d\n", valor, pos);
            }
            else {
                printf("Erro ao inserir!\n");
            }
            salvarDados();
            break;
            }

        case 2: {
            int valor;
            printf("Digite um valor para inserir no final do array: ");
            scanf("%d", &valor);
            if (inserirFinal(valor)) {
                printf("Valor %d inserido no final\n", valor);
            }
            else {
                printf("Erro: vetor cheio!\n");
            }
            salvarDados();
            break;
            }

        case 3: {
            int posi_excluir;
            printf("Digite uma posição do array para excluir: ");
            scanf("%d", &posi_excluir);
            if (removerPosicao(posi_excluir)) {
                printf("Posição %d removida\n", posi_excluir);
            }
            else {
                printf("Erro: posição inválida!\n");
            }
            salvarDados();
            break;
            }

        case 4: {
            int valor;
            printf("Digite um valor para remover do array: ");
            scanf("%d", &valor);
            if (removerValor(valor)) {
                printf("Valor %d removido\n", valor);
            }
            else {
                printf("Valor não encontrado!\n");
            }
            salvarDados();
            break;
            }

        case 5: {
            int valor;
            printf("Digite um valor para buscar no array: ");
            scanf("%d", &valor);
            int pos = buscarValor(valor);
            if (pos != -1) {
                printf("Valor %d encontrado na posição %d\n", valor, pos);
            }
            else {
                printf("Valor %d não encontrado\n", valor);
            }
            salvarDados();
            break;
            }

        case 6: {
            imprimirVetor();
            break;
        }
    }

    return 0;
}