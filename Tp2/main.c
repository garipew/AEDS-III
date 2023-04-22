#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol;
    FILE* e;
    Grafo* g = criaGrafo();

    if(argc < 3){
        printf("Missing arguments <int> <filename>.\n");
        exit(-1);
    }

    sol = atoi(argv[1]);

    e = fopen(argv[2], "r");
    if(e == NULL){
    printf("Falha ao ler o arquivo \"%s\".\n", argv[2]);
    }

    printf("solucao %d\nentrada: %s\n", sol, argv[2]);

    apagaGrafo(g);
    
}