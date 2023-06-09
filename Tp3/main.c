#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>

void main(int argc, char* argv[]){

    FILE* entrada;
    FILE* saida;

    Lista* padrao;
    Lista* texto;

    int T;
    char s[100];
    char c;

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

    for(int i = 0; i < T; i++){
        padrao = criaListaVazia();
        texto = criaListaVazia();

        // Coletando padrão e texto
        while((c = getc(entrada)) != ' '){
            inserir(padrao, criaItem(c));
        }
        while((c = getc(entrada)) != EOF){
            if(c == '\n'){
                break;
            }
            inserir(texto, criaItem(c));
        }

        // Executando solução selecionada
        sol(texto, padrao, saida, argv[2]);
        

        deletaLista(padrao);
        deletaLista(texto);

    }

    fclose(entrada);
    fclose(saida);

}