#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>


void main(int argc, char* argv[]){

    int sol;
    char entrada[200];

    sol = atoi(argv[1]);
    if(argv[2] == NULL){
        printf("Arquivo não encontrado.\n");
        exit(-1);
    }
    strcpy(entrada, argv[2]);

    printf("solucao %d\nentrada: %s\n", sol, entrada);


}