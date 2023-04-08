#include "segmento.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char **argv){
    
    struct timeval t1, tf;
    FILE *input;
    FILE *output;
    int opt;
    char inp[200];
    char out[200];

    gettimeofday(&t1, NULL);

    while((opt = getopt(argc, argv, "i:o:")) != -1){
        switch(opt){
            case 'i':
                strcpy(inp, optarg);
                break;
            case 'o':
                strcpy(out, optarg);
                break;
            default:
                printf("Opção inválida.\n");
                exit(-1);
        }
    }
    
    Lista* l;

    int N, Xa, Xb, x, y;

    input = fopen(inp, "r");
    output = fopen(out, "w");

    if(input == NULL || output == NULL){
        printf("Arquivo não encontrado.\n");
        exit(-1);
    }

    fscanf(input, "%d %d %d", &N, &Xa, &Xb);

    l = criaListaVazia(criaItem(Xa, 0), criaItem(Xb, 0));

    for(int i = 0; i < N; i++){
        fscanf(input, "%d %d", &x, &y);
        inserir(l, criaItem(x, y));
    }

    fclose(input);

    fprintf(output, "%d\n", conectados(l));
    fclose(output);

    deletaLista(l);

    gettimeofday(&tf, NULL);

    return;

}
