#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

void main(int argc, char* argv[]){

    FILE* entrada;
    FILE* saida;

    char s[100];
    char out[] = "out";
    int contador = 0;
    Lista* padrao;
    Lista* texto;
    Item* a;

    Item* atualP;
    Item* atualT;
    int inicioC;

    int T;
    char c;

    if(argc < 2){
        printf("Esperado argumentos <entrada> e <caso_teste>\n");
        exit(-1);
    }

    entrada = fopen(argv[1], "r");
    if(entrada == NULL){
        printf("Falha ao ler arquivo %s.\n", argv[1]);
        exit(-1);
    }

    fscanf(entrada, "%d ", &T);

    for(int i = 0; i < T; i++){
        padrao = criaListaVazia();
        texto = criaListaVazia();

        while((c = getc(entrada)) != ' '){
            inserir(padrao, criaItem(c));
        }
        while((c = getc(entrada)) != EOF){
            if(c == '\n'){
                break;
            }
            inserir(texto, criaItem(c));
        }

        
        sol1(texto, padrao);
        

        deletaLista(padrao);
        deletaLista(texto);

    }

    fclose(entrada);

}