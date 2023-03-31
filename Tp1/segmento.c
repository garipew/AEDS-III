#include "segmento.h"
#include <stdio.h>
#include <stdlib.h>

Segmento* criarSegmento(Item* pI, Item* pF){
    
    Segmento* seg = (Segmento*)malloc(sizeof(Segmento));
    seg->pontoI = pI;
    seg->pontoF = pF;

    return seg;

}

int checarInterseção(Segmento* a, Segmento* b){

    // A seguinte função tem como objetivo calcular a intersecção entre dois segmentos
    // baseando-se em seus respectivos pontos iniciais e finais.

    if(a == NULL || b == NULL){
        return 0;
    }

    double res;
    int difBx = (b->pontoF->coord[0] - b->pontoI->coord[0]);
    int difAx = (a->pontoF->coord[0] - a->pontoI->coord[0]);
    int difBy = (b->pontoF->coord[1] - b->pontoI->coord[1]);
    int difAy = (a->pontoF->coord[1] - a->pontoI->coord[1]);
    double s, t;
    
    res = (difBx * difAy) - (difAx *difBy);

    if(res == 0.00)
        return 0;

    s = (difBx * (b->pontoI->coord[1] - a->pontoI->coord[1]) - difBy * (b->pontoI->coord[0] - a->pontoI->coord[0]))/res; 
    t = (difAx * (b->pontoI->coord[1] - a->pontoI->coord[1]) - difAy * (b->pontoI->coord[0] - a->pontoI->coord[0]))/res;

    if(s > 1 || s < 0){
        return 0;
    }
    if(t > 1 || t < 0){
        return 0;
    }    
    return 1;
    
    //O(1)

};

int conectados(Lista* l){

    int conecta = 0;
    int max = 0;
    Item* i = l->ultimo;
    Item* j = l->ultimo;
    Lista* vertices = criaListaVazia(criaItem(0, 0, 0), criaItem(0, 0, 0));
    Segmento* aux1 = NULL;
    Segmento* aux2 = NULL;
    Segmento* antXa = NULL;
    Segmento* antXb = NULL;
    Segmento* atualXa;
    Segmento* atualXb;

    while(j != l->primeiro){

        if(l->tamanho - vertices->tamanho <= max){
            break;
        }

        while(i != l->primeiro){

            if(buscarElemento(vertices, i->id)){
                break;
            }


            atualXa = criarSegmento(l->ancoras[0], i);
            atualXb = criarSegmento(l->ancoras[1], i);

            i = i->anterior;

            if(checarInterseção(atualXa, antXb) || checarInterseção(atualXb, antXa)){
                
                aux1 = atualXa;
                aux2 = atualXb;
                atualXa = NULL;
                atualXb = NULL;

                free(aux1);
                free(aux2);
                
            } 
            else{
            
                conecta++;

                aux1 = antXa;
                aux2 = antXb;

                antXa = atualXa;
                antXb = atualXb;

                inserir(vertices, criaItem(atualXa->pontoF->coord[0], atualXa->pontoF->coord[1], 
                atualXa->pontoF->id));

                free(aux1);
                free(aux2);
            }

        }

        // somatorio(i=1->n) de i == (n²+n)/2 = O(n²)
    
        if(conecta >= max){
            max = conecta;
        }
        conecta = 0;
        j = j->anterior;
        i = j;
    }

    free(atualXa);
    free(atualXb);
    if(antXa!=atualXa){
        free(antXa);
        free(antXb);
    }

    deletaLista(vertices);
    return max;
    
    // O(n²)
}
