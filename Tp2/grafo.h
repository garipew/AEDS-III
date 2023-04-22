#include "lista.h"


typedef struct vertice{

    Lista* adjacentes;
    int id;
    int valor;

    struct vertice* ant;
    struct vertice* prox;

} Vertice;


typedef struct grafo{

    Vertice* primeiro;
    Vertice* ultimo;
    int tamanho;

} Grafo;


Grafo* criaGrafo();
Vertice* criaVertice(int);
void insereVertice(Vertice*, Grafo*);
void insereAresta(Grafo*, int, int, int);
int existeAresta(int, int, Grafo*);
void imprimeArestas(Vertice* v);
Vertice* caminharAresta(Vertice*, int);
Vertice* percorrerAresta(Vertice*);
void removeVertice(int, Grafo*);
void apagaGrafo(Grafo*);