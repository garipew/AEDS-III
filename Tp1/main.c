#include "segmento.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void main(int argc, char **argv){
    
    struct timeval t1, tf;
    FILE *input;
    FILE *output;

    gettimeofday(&t1, NULL);
    
    Lista* l;

    int N, Xa, Xb, x, y;

    input = fopen("input", "r");
    output = fopen("output", "w");

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
