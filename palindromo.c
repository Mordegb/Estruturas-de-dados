#include <stdio.h>
#include <string.h>

int main() {
    char palavra[50];
    printf("Digite uma palavra de até 50 letras: ");
    scanf("%s", palavra);
    int tam = strlen(palavra);

    char aux[tam + 1]; // +1 para o terminador nulo
    int j = 0;
    
    for(int i = tam - 1; i >= 0; i--) {
        aux[j] = palavra[i];
        j++;
    }
    
    aux[j] = '\0'; 

    printf("Original: %s\n", palavra);
    printf("Invertida: %s\n", aux);

    if(strcmp(palavra, aux) == 0) {
        printf("É palíndromo\n");
    } else {
        printf("Não é palíndromo.\n");
    }

    return 0;
}