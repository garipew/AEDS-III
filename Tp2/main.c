#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol;
    FILE* e;
    Arvore* teste = cria_arvore_vazia();

    teste->raiz = insere(cria_no(5), 1);
    teste->raiz = insere(teste->raiz, 4);

    pre_ordem(teste, teste->raiz);
    printf("\n");
    pos_ordem(teste, teste->raiz);
    printf("\n");
    ordem_central(teste, teste->raiz);
    printf("\n");

    /*
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
    */

}