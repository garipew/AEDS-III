#include "segmento.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char **argv){
    
    /*
    struct timeval t1, tf;


    gettimeofday(&t1, NULL);

    struct rusage inicio, fim;
    getrusage(RUSAGE_SELF, &inicio);

    float tCPU;
    */

    FILE *input;
    FILE *output;
    int opt;
    char inp[200];
    char out[200];


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

    /*
    gettimeofday(&tf, NULL);
    printf("%.06fs\n", ((tf.tv_sec-t1.tv_sec) + 1e-6*(float)(tf.tv_usec-t1.tv_usec)));

    getrusage(RUSAGE_SELF, &fim);

 
    tCPU = (fim.ru_utime.tv_sec - inicio.ru_utime.tv_sec) + 1e-6*(fim.ru_utime.tv_usec - inicio.ru_utime.tv_usec);
    printf("%.06fs\n", tCPU);
    */
 
    return;

}
