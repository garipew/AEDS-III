#include "grafoV2.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol, R, C, testes;
    FILE* e;
    Grafo* g;
    char linha[200];

    if(argc < 3){
        printf("Esperado argumentos <int> <arquivo.txt>.\n");
        exit(-1);
    }

    sol = atoi(argv[1]);

    e = fopen(argv[2], "r");

    if(e == NULL){
    printf("Falha ao ler o arquivo \"%s\".\n", argv[2]);
    }

    fscanf(e, "%d", &testes);
    for(int i = 0; i < testes; i++){
        
        g = criaGrafo();

        printf("caso teste %d\n", i+1);
        fscanf(e, "%d %d", &R, &C);

        printf("Ler %d x %d números.\n", R, C);
        fgetc(e);
        
        coletaDados(g, R, C, e);

        desenhaGrafo(g);
        apagaGrafo(g);
        printf("\n\n");
    }


    
}