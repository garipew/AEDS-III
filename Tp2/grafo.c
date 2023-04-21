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

    if(orig->arestas == NULL)
        orig->arestas = criaListaVazia();
    inserir(orig->arestas, criaItem(), peso, dest);

}

void removeVertice(int destino, Grafo* g){

    if(g->tamanho==0)
        return;
    
    Vertice* atual = g->primeiro;
    Vertice* aux;

    while(atual->prox != NULL){

        if(atual->prox->id == destino){
            if(!listaVazia(atual->prox->arestas)){
                deletaLista(atual->prox->arestas);
            }
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

/*
Vertice* buscaVertice(int id, Vertice* raiz){

    Vertice* v;

    if(raiz->arestas->tamanho == 0){
        return NULL;
    }

    v = raiz;
    v->arestas = raiz->arestas;

    while(v != NULL){
        if(v->id = id)
            return v;
        v->arestas = v->prox->arestas;
        v = v->prox;
    }

    return v;

}

void percorrerVertice(Vertice* raiz, Lista* l){

    Item* atual;
    Vertice* vAtual;

    printf("%d %d->\n", raiz->id, listaVazia(l));
    if(listaVazia(l)){
        printf("lista vazia, voltando\n");
        return;
    }

    atual = l->primeiro->proximo;
    printf(" %d\n", atual->destino); 
    if(atual->destino == vAtual->id){
        return;
    }   

    while(atual != NULL){
        vAtual = buscaVertice(atual->destino, raiz);
        percorrerVertice(vAtual, vAtual->arestas);
        atual = atual->proximo;
    }
}
*/
void apagaGrafo(Grafo* g){

    int t = g->tamanho;

    for(int i = 0; i <= t; i++){
        removeVertice(g->ultimo->id, g);
    }

    Vertice* c = g->primeiro;

    free(c);
    free(g);

}