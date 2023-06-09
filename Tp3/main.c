#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

void main(int argc, char* argv[]){

    FILE* entrada;
    FILE* saida;

    Lista* padrao;
    Lista* texto;

    int T;
    char s[100];

    // Verificando parâmetros
    if(argc < 2){
        printf("Esperado argumentos <entrada> e <caso_teste>\n");
        exit(-1);
    }

    entrada = fopen(argv[1], "r");
    if(entrada == NULL){
        printf("Falha ao ler arquivo %s.\n", argv[1]);
        exit(-1);
    }

    // Construindo arquivo de saída    
    strncpy(s, argv[1], (strlen(argv[1]) - 3));
    strcat(s, "out");

    saida = fopen(s, "w");
    if(saida == NULL){
        printf("Falha ao escrever arquivo %s.\n", s);
        exit(-1);
    }

    // Executando casos-teste
    fscanf(entrada, "%d ", &T);

    casosTeste(T, entrada, saida, argv[2]);

    fclose(entrada);
    fclose(saida);

}