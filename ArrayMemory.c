#include <stdio.h>
#include <stdbool.h>
#define max 100
#define arquivo "lista_valores.txt"
int qtn = 0;
int vetor[max];

void salvarDados(){
	FILE *file = fopen(arquivo , "w");
	if(file == NULL){
		printf("error ao criar o arquivo");
		return;
	}
	//escreve no arquivo a quantidade de valores
	fprintf(file,"%d\n",qtn);

	//escreve no array cada elemento do vetor
	for(int i = 0;i < qtn;i++){
		fprintf(file,"%d\n",vetor[i]);
	}
	fclose(file);
	printf("deu bom salvar os arquivos");

}

void carregarDados(){
	FILE *file = fopen(arquivo , "r");
	if(file == NULL){
		printf("arquivo não encontrado, fudeu, começa dnv\n");
		return;
	}

	//lê a quantidade de valores do array no arquivo
	fscanf(file,"%d",&qtn);

	//le cada valor do array do arquivo e colocar na memoria
	for(int i = 0; i < qtn;i++){
		fscanf(file,"%d",&vetor[i]);
	}

	fclose(file);
	printf("deu bom carregar\n\n");

}

bool inserirFinal(int valor){
	if(qtn == max){
		return false;
	}

	if(valor < 0){
		printf("valor invalido");
		return false;
	}

	vetor[qtn] = valor;
	qtn++;
	return true;
}

bool inserirPorIndice(int valor,int posi){
	if(posi < 0 || posi > qtn || qtn == max){
		return false;
	}
	//move todos os numero a partid da posição pra direira
	for(int i = qtn; i > posi; i--){
		vetor[i] = vetor[i - 1];
	}
	vetor[posi] = valor;
	qtn ++;
	return true;
 }

 int buscaValor(int valor){
 	//procura o numero percorrendo o array
 	for(int i = 0; i < qtn; i++){
 		if(vetor[i] == valor){
 		return i;
 		}
 	}
 	return -1;
 }

 bool removerPosicao(int posi){
 	if(posi < 0 || posi >= qtn){
 		return false;
 	}
 	for(int i = posi; i < qtn - 1; i++){
 		vetor[i] = vetor[i + 1];
 	}
 	qtn--;
 	return true;

 }

 bool removerValor(int valor){
	if(valor < 0 ){
		return false;
	}
	for(int i = 0; i < qtn; i++){
		if(vetor[i] == valor){
			return removerPosicao(i);
		}
	}

	return false;
 }

 void imprimirArray(){
 	printf("[");
 	for(int i = 0; i < qtn; i++){
 		printf("%d ,", vetor[i]);
 	}
 	printf("]\nQuantidade: %d\n\n", qtn);
 }

 int main(){

    // Carrega os dados ao iniciar o programa
    carregarDados();

    int opt;
    printf("1 - inserir valor .      2 - inserir no por indice.\n");
    printf("3 - excluir posição.     4 - remover valor.\n");
    printf("5 - buscar valor.        6 - imprimir array.\n");
    scanf("%d", &opt);

    switch (opt) {
        case 1: {
            int valor;
            printf("digite um valor para inserir no final do array: ");
            scanf("%d", &valor);
            if (inserirFinal(valor)) {
                printf("valor %d inserido no final.\n", valor);
            }
            else {
                printf("não deu pra inseir pq o array ta cheio.\n");
            }
            salvarDados();
        	imprimirArray();
            break;
            }

        case 2: {
            int valor, pos;
            printf("digite um valor para inserir no array: ");
            scanf("%d", &valor);
            printf("colocar o valor %d em qual posição do array: " , valor);
            scanf("%d", &pos);
            if (inserirPorIndice(valor, pos)) {
                printf("Valor %d inserido na posição %d\n", valor, pos);
            }
            else {
                printf("se isso apareceu, fudeu, pq não deu pra inserir não , ai dento kkkkkkk\n");
            }
            salvarDados();
        	imprimirArray();
            break;
            }


        case 3: {
            int posi_excluir;
            printf("digite uma posição do array para excluir: ");
            scanf("%d", &posi_excluir);
            if (removerPosicao(posi_excluir)) {
                printf("posição %d removida\n", posi_excluir);
            }
            else {
                printf("posição inválida.\n");
            }
            salvarDados();
        	imprimirArray();
            break;
            }

        case 4: {
            int valor;
            printf("digite um valor para remover do array: ");
            scanf("%d", &valor);
            if (removerValor(valor)) {
                printf("valor %d removido\n", valor);
            }
            else {
                printf("valor não encontrado!\n");
            }
            salvarDados();
        	imprimirArray();
            break;
            }

        case 5: {
            int valor;
            printf("digite um valor para buscar no array: ");
            scanf("%d", &valor);
            int pos = buscaValor(valor);
            if (pos != -1) {
                printf("valor %d encontrado na posição %d\n", valor, pos);
            }
            else {
                printf("valor %d não encontrado\n", valor);
            }
        	imprimirArray();
            break;
            }

        case 6: {
            imprimirArray();
            break;
        }
    }

    return 0;
}
