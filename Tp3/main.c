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

    int T;
    char c;

    entrada = fopen(argv[1], "r");

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

        imprimeLista(padrao);
        imprimeLista(texto);
        
        deletaLista(padrao);
        deletaLista(texto);
    }


}