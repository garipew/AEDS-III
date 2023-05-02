#include "grafoV2.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol, R, C, testes;
    FILE* e;
    FILE* s;
    Grafo* g;

    if(argc < 3){
        printf("Esperado argumentos <int> <arquivo.txt>.\n");
        exit(-1);
    }

    sol = atoi(argv[1]);

    e = fopen(argv[2], "r");
    s = fopen("saida.txt", "w");

    if(e == NULL){
    printf("Falha ao ler o arquivo \"%s\".\n", argv[2]);
    }

    fscanf(e, "%d", &testes);
    for(int i = 0; i < testes; i++){
        
        g = criaGrafo();

        fscanf(e, "%d %d", &R, &C);
        
        coletaDados(g, R, C, e);
    
        solucao(g, sol, s);

        apagaGrafo(g);
    }

    fclose(e);
    fclose(s);
    
}