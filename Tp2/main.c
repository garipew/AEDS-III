#include "grafoV2.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>


void main(int argc, char* argv[]){

    /*
    struct timeval t1, tf;

    gettimeofday(&t1, NULL);

    struct rusage inicio, fim;
    getrusage(RUSAGE_SELF, &inicio);

    float tCPU;
    */

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

        solucao(g, sol, C, s);

        apagaGrafo(g);

    }

    fclose(e);
    fclose(s);

    /*
    gettimeofday(&tf, NULL);
    printf("%.06fs\n", ((tf.tv_sec-t1.tv_sec) + 1e-6*(float)(tf.tv_usec-t1.tv_usec)));

    getrusage(RUSAGE_SELF, &fim);
 
    tCPU = (fim.ru_utime.tv_sec - inicio.ru_utime.tv_sec) + 1e-6*(fim.ru_utime.tv_usec - inicio.ru_utime.tv_usec);
    printf("%.06fs\n", tCPU);
    */
    
}