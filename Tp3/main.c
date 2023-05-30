#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

void main(int argc, char* argv[]){

    FILE* entrada;
    FILE* saida;

    char s[100];
    char out[] = "out";
    int contador = 0;

    
    printf("%s\n", argv[1]);
    strcpy(s, argv[1]);

    while(s[contador] != '.'){
        contador++;
    }

    for(int i = 0; i < 3; i++){
        s[contador+i+1] = out[i];
    }
    printf("%s\n", s);

}