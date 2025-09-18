#include <stdio.h>

int main(){

    int parada;
    printf("informe a quantidade de numeros da sequencia: ");
    scanf("%d" , &parada);
   int p1 = 0;
   int p2 = 1;
   int p3 = 0;
   
   
   for(int i = 1; i < parada; i++){
       printf("%d\n" , p3);
       if(p3 == 0 ){
           p3  += 1;
           printf("1\n");
    }

    p1 = p2;
    p2 = p3;
    p3 = p2 + p1;

   }


    return 0;
}