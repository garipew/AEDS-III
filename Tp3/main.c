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

        a = texto->ultimo->anterior;
        while(a->anterior != NULL){
            inserir(texto, criaItem(a->id));
            a = a->anterior;
        }

        atualT = texto->primeiro->proximo;
        atualP = padrao->primeiro->proximo;
        while(atualT != NULL){

            if(atualT->id == atualP->id){
                if(atualP->indice == 0){
                    inicioC = atualT->indice;
                }
                if(atualP->indice == padrao->ultimo->indice){
                    printf("S %d\n", inicioC+1);
                    break;
                }
                atualP = atualP->proximo;
            }else if((atualT->id != atualP->id)){
                atualP = padrao->primeiro->proximo;
                if(inicioC != -1){
                    while(atualT->indice != inicioC){
                        atualT = atualT->anterior;
                    }
                    inicioC = -1;
                }
            }
            
            atualT = atualT->proximo;
        }
        inicioC = -1;
        if(atualP->indice != padrao->ultimo->indice){
            printf("N\n");
        }

        
        deletaLista(padrao);
        deletaLista(texto);
    }


}