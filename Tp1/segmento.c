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
    
    //O(1)

};

int conectados(Lista* l){

    int conecta = 0;
    int max = 0;
    Item* i = l->ultimo;
    Item* j = l->ultimo;
    Lista* vertices = criaListaVazia(criaItem(0, 0), criaItem(0, 0));
    Segmento* aux1 = NULL;
    Segmento* aux2 = NULL;
    Segmento* antXa = NULL;
    Segmento* antXb = NULL;
    Segmento* atualXa;
    Segmento* atualXb;

    //printf("Flag 2\n");

    while(j != l->primeiro){
        //printf("Flag 3\n");
        // somatorio(i=0->n-1) de n 

        if(l->tamanho - vertices->tamanho <= max){
            break;
        }

        while(i != l->primeiro){
            
            //O(n)

            //printf("Flag 4, conecta: %d\n", conecta);


            if(buscarElemento(vertices, i->id)){
                //printf("break interno\n");
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
                //printf("Conecta (%d, %d)\n", atualXa->pontoF->coord[0], atualXa->pontoF->coord[1]);
                conecta++;

                aux1 = antXa;
                aux2 = antXb;

                antXa = atualXa;
                antXb = atualXb;

                inserir(vertices, atualXa->pontoF);

                free(aux1);
                free(aux2);
            }

        }
    
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
        //imprimeLista(l);
        //printf("===========\n");
        //imprimeLista(vertices);
        deletaLista(vertices);

    return max;
    
    // O(n) * O(n) = O(n²)
}
