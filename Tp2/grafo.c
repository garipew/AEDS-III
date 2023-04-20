#include "grafo.h"
#include <stdlib.h>


Vertice* verticeCabeca(){

    Vertice* v = (Vertice*)malloc(sizeof(Vertice));

    v->id = -1;

    return v;

};


Grafo* criaGrafo(){

    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    Item* origem = verticeCabeca(); 

    g->primeiro = origem;
    g->ultimo = origem;

    g->tamanho = 0;

    g->primeiro->prox = NULL;
    g->ultimo->ant = NULL;

    return g;

}


Vertice* criaVertice(){

    Vertice* v = (Vertice*)malloc(sizeof(Vertice));

    v->prox = NULL;
    v->ant = NULL;
    v->arestas = NULL;

    v->id = 0;

}


void insereVertice(Vertice* v, Grafo* g){

    if(g->tamanho == 0)
        g->primeiro = v;

    v->ant = g->ultimo;
    g->ultimo->prox = v;
    g->ultimo = v;
    g->tamanho++;

    v->id = g->tamanho;

}

void insereAresta(Vertice* orig, int dest, int peso){

    inserir(orig->arestas, criaItem(), peso, dest);

}

