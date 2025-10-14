#include <stdio.h>
#include <stdlib.h>
void limpaBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int main() {


	int* qtd;
	qtd = (int*)malloc(sizeof(int));

	if(qtd == NULL) {
		printf("Erro: nao foi possivel alocar memoria!\n");
		return 1;
	}

	printf("quantos sensores ja foram instalados?: ");
	scanf("%d", qtd);
	limpaBuffer();
	printf("\n");

	if(*qtd <= 0) {
		printf("Erro: quantidade de sensores deve ser maior que zero!\n");
		free(qtd);
		return 1;
	}

	float* leituras = (float*)malloc(*qtd * sizeof(float));

	if(leituras == NULL) {
		printf("Erro: nao foi possivel alocar memoria para as leituras!\n");
		free(qtd);
		return 1;
	}

	for(int i = 0; i < *qtd; i++) {
		printf("leituras da maquina %d: ", i);
		scanf("%f", &leituras[i]);
		limpaBuffer();

	}

	for(int i = 0; i < *qtd; i++) {
		printf("maquina[%d]\n", i);
		printf("temperatura: %.2f\n\n", leituras[i]);
	}

	printf("novas leituras foram feitas?\n");
	char res;
	scanf("%c", &res);
	limpaBuffer();
	if (res == 's' || res == 'S')  {

		int* novaQtd = (int*)malloc(sizeof(int));
		printf("qual a quantidade de maquinas agora?");
		scanf("%d", novaQtd);
		limpaBuffer();

		qtd = (int*)realloc(qtd, *novaQtd * sizeof(int));
		leituras = (float*)realloc(leituras, *novaQtd * sizeof(float));

		for(int i = (*qtd + 1); i < (*novaQtd - *qtd); i++) {
			printf("maquina[%d]\n", i);
			scanf("%f", &leituras[i]);
			limpaBuffer();
		}
		printf("\n");

		for(int i = 0; i < *qtd; i++) {
			printf("maquina[%d]\n", i);
			printf("temperatura: %.2f\n\n", leituras[i]);
		}

		free(novaQtd);
		free(leituras);
		free(qtd);
		return 0;


	}
	else {
		free(leituras);
		free(qtd);

		return 0;
	}

}