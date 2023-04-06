#include "segmento.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


void main(int argc, char **argv){

    struct timeval t1, tf;

    gettimeofday(&t1, NULL);
    
    Lista* l;

    int N, Xa, Xb, x, y;

    scanf("%d %d %d", &N, &Xa, &Xb);

    l = criaListaVazia(criaItem(Xa, 0), criaItem(Xb, 0));

    for(int i = 0; i < N; i++){
        scanf("%d %d", &x, &y);
        inserir(l, criaItem(x, y));
    }


    printf("%d\n", conectados(l));

    deletaLista(l);

    gettimeofday(&tf, NULL);

    return;

}
