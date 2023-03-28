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

    // Seguindo a formula temos que caso [ (bXFinal - bXInicial) * (aYFinal - aYInicial) - 
    //                          (bYFinal - bYInicial) * (aXFinal - aXInicial) = 0 ] não há interseção.

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


};

int conectados(Lista* l){

    int conecta = 0;
    Item* aux = l->ultimo;
    Segmento* aux1 = NULL;
    Segmento* aux2 = NULL;
    Segmento* antXa = NULL;
    Segmento* antXb = NULL;
    Segmento* atualXa;
    Segmento* atualXb;

    while(aux != l->primeiro){


        atualXa = criarSegmento(l->ancoras[0], aux);
        atualXb = criarSegmento(l->ancoras[1], aux);

        aux = aux->anterior;

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

            free(aux1);
            free(aux2);
        }
        

    }

    free(atualXa);
    free(atualXb);
    if(antXa!=atualXa){
        free(antXa);
        free(antXb);
    }

    return conecta;
}