#include "lista.h"


typedef struct vertice{

    Lista* arestas;
    int id;

    struct vertice* ant;
    struct vertice* prox;

} Vertice;


typedef struct grafo{

    Vertice* primeiro;
    Vertice* ultimo;
    int tamanho;

} Grafo;


Grafo* criaGrafo();
Vertice* criaVertice();
void insereVertice(Vertice*, Grafo*);
void insereAresta(Vertice*, int, int, int);