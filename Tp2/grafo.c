#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>

Vertice* verticeCabeca(){

    Vertice* v = (Vertice*)malloc(sizeof(Vertice));

    v->id = -1;

    return v;

};


Grafo* criaGrafo(){

    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    Vertice* origem = verticeCabeca(); 

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
    v->arestas = criaListaVazia();

    v->id = 0;

}


void insereVertice(Vertice* v, Grafo* g){

    if(g->tamanho == 0)
        g->primeiro->prox = v;

    v->ant = g->ultimo;
    g->ultimo->prox = v;
    g->ultimo = v;
    g->tamanho++;

    v->id = g->tamanho;

}

void insereAresta(Vertice* orig, int peso, int dest){

    inserir(orig->arestas, criaItem(), peso, dest);

}

void imprimeArestas(Vertice* v){

    Lista* a = v->arestas;
    Item* aux = a->primeiro->proximo;

    while(aux != NULL){

        printf("%d -> %d; ", v->id, aux->destino);
        aux = aux->proximo;

    }
    printf("\n");

}

Vertice* caminharAresta(Vertice* origem, int destino){

    Vertice* atual = origem;

    while(atual!=NULL){
        if(atual->id == destino)
            return atual;
        atual = atual->prox;
    }
    return NULL;

}

Vertice* percorrerAresta(Vertice* origem){

    Vertice* atual = origem;
    Lista* arestas = origem->arestas;

    while(!listaVazia(atual->arestas)){
        printf("%d -> ", atual->id);
        atual = caminharAresta(origem, arestas->primeiro->proximo->destino);
        arestas = atual->arestas;
    }
    printf("%d\n", atual->id);

    return atual;

}

void removeVertice(int destino, Grafo* g){

    if(g->tamanho==0)
        return;
    
    Vertice* atual = g->primeiro;
    Vertice* aux;

    while(atual->prox != NULL){

        if(atual->prox->id == destino){

            deletaLista(atual->prox->arestas);
            aux = atual->prox;
            atual->prox = atual->prox->prox;
            
            if(aux->prox == NULL)
                g->ultimo = atual;
            
            g->tamanho--;
            if(g->tamanho == 0)
                g->ultimo = g->primeiro;
            if(aux != NULL)
                free(aux);
            return;
        }

        atual = atual->prox;

    }

}

void apagaGrafo(Grafo* g){

    int t = g->tamanho;

    for(int i = 0; i <= t; i++){
        removeVertice(g->ultimo->id, g);
    }

    Vertice* c = g->primeiro;

    free(c);
    free(g);

}