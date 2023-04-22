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


Vertice* criaVertice(int valor){

    Vertice* v = (Vertice*)malloc(sizeof(Vertice));

    v->prox = NULL;
    v->ant = NULL;
    v->valor = valor;
    v->adjacentes = criaListaVazia();

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

Vertice* encontraVertice(Grafo* g, int id){

    Vertice* origem = g->primeiro->prox;

    while(origem != NULL){
        if(origem->id == id){
            break;
        }
        origem = origem->prox;
    }

    return origem;

}

void insereAresta(Grafo* g, int origem, int dest, int peso){

    Vertice* orig = encontraVertice(g, origem);

    if(orig!=NULL)
        inserir(orig->adjacentes, criaItem(), peso, dest);

}

int existeAresta(int v1, int v2, Grafo* g){

    Vertice* origem = encontraVertice(g, v1);

    if(origem == NULL)
        return 0;

    return buscarElemento(origem->adjacentes, v2);
    // Vertice* destino = g->primeiro->prox;

}

void retiraAresta(int v1, int v2, Grafo* g){

    Vertice* origem = encontraVertice(g, v1);

    removeElemento(origem->adjacentes, v2);

}

void imprimeArestas(Vertice* v){

    Lista* a = v->adjacentes;
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
    Lista* adjacentes = origem->adjacentes;

    while(!listaVazia(atual->adjacentes)){
        printf("%d -> ", atual->id);
        atual = caminharAresta(origem, adjacentes->primeiro->proximo->destino);
        adjacentes = atual->adjacentes;
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

            deletaLista(atual->prox->adjacentes);
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