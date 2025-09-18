#include <stdio.h>
#include <string.h>
int main() {

    char palavra[50];
    printf("diga uma palavra de ate 50 letras:");
    scanf("%s" ,palavra );
    int tam = strlen(palavra);

    char aux[tam];
    int j = 0;
    for(int i = tam - 1; i >= 0 ; i--){
        aux[j] = palavra[i];
        j += 1;
    }

    printf("%s\n" , aux);
    printf("%s\n" , palavra);

    if(strcmp(palavra,aux)){
        printf("é palindromo");
    }
    else{
        printf("não é palindromo\n");
    }

    return 0;
}