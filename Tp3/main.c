#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include <sys/time.h>


void main(int argc, char* argv[]){

/*
    struct timeval t1, tf;
    gettimeofday(&t1, NULL);
*/


    FILE* entrada;
    FILE* saida;

    Lista* padrao;
    Lista* texto;

    int T;
    char s[100];

    // Verificando parâmetros
    if(argc < 2){
        printf("Esperado argumentos <entrada> e <caso_teste>\n");
        exit(-1);
    }

    entrada = fopen(argv[1], "r");
    if(entrada == NULL){
        printf("Falha ao ler arquivo %s.\n", argv[1]);
        exit(-1);
    }

    // Construindo arquivo de saída    
    strncpy(s, argv[1], (strlen(argv[1]) - 3));
    strcat(s, "out");

    saida = fopen(s, "w");
    if(saida == NULL){
        printf("Falha ao escrever arquivo %s.\n", s);
        exit(-1);
    }

    // Executando casos-teste
    fscanf(entrada, "%d ", &T);

    casosTeste(T, entrada, saida, atoi(argv[2]));

    fclose(entrada);
    fclose(saida);

/*
    gettimeofday(&tf, NULL);
    printf("%.06fs\n", ((tf.tv_sec-t1.tv_sec) + 1e-6*(float)(tf.tv_usec-t1.tv_usec)));
*/

}