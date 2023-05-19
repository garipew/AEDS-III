#include "fila.h"
#include <stdio.h>

typedef struct vertice{

	Lista* adjacentes;
	int id;
	int valor;
	int hpFinal;
	int hpMin;

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
int solucao1(Grafo*);
void solucao2(Grafo*, Vertice*, int, int);
int solucao3(Grafo*, int);
void solucao(Grafo*, int, int, FILE*);