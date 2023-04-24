#include "lista.h"
#include <stdio.h>

typedef struct vertice{

	Lista* adjacentes;
	int id;
	int valor;

	struct vertice* prox;
	struct vertice* ant;

} Vertice;


typedef struct grafo{
	
	Vertice* primeiro;
	Vertice* ultimo;
	int tamanho;

} Grafo;


Grafo* criaGrafo();
void insereVertice(Grafo*, int);
void insereAresta(Grafo*, int, int, int);
int existeAresta(Grafo*, int, int);
Lista* obtemAdjacentes(Grafo*, int);
void removeAresta(Grafo*, int, int, int);
void apagaGrafo(Grafo*);
void desenhaGrafo(Grafo*);
Grafo* transposto(Grafo*);
int obtemMin(Grafo*);
void coletaDados(Grafo*, int, int, FILE*);
