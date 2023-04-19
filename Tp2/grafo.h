#include "lista.h"

typedef struct grafo{

    Vertice* inicial;
    int tamanho;

} Grafo;

typedef struct vertice{

    Lista* arestas;
    int id;

} Vertice;

Grafo* criaGrafo();
Vertice* criaVertice();
void insereVertice(Vertice*, Grafo*);
void insereArestas(Lista*, Vertice*);