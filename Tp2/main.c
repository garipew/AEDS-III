#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol, R, C, testes, valor;
    FILE* e;
    Grafo* g;

    if(argc < 3){
        printf("Esperado argumentos <int> <filename>.\n");
        exit(-1);
    }

    sol = atoi(argv[1]);

    e = fopen(argv[2], "r");
    if(e == NULL){
    printf("Falha ao ler o arquivo \"%s\".\n", argv[2]);
    }

    //printf("solucao %d\nentrada: %s\n", sol, argv[2]);

    fscanf(e, "%d", &testes);
    for(int i = 0; i < testes; i++){

        fscanf(e, "%d %d", &R, &C);
        g = criaGrafo();

        for(int j = 0; j < R; j++){
            
            fscanf(e, "%d", &valor);
            insereVertice(criaVertice(valor), g);
            insereAresta(g, j+1, 1, j+2);

        }

        imprimeArestas(g->primeiro->prox->prox);

        apagaGrafo(g);

    }


    
}