#include "grafoV2.h"
#include <stdlib.h>
#include <stdio.h>

Grafo* criaGrafo(){

	Grafo* g = (Grafo*)malloc(sizeof(Grafo));
	Vertice* origem = criaVertice(0);
	g->tamanho = 0;

	g->primeiro = origem;
	g->ultimo = origem;
	
	return g;

}

Vertice* criaVertice(int valor){

	Vertice* v = (Vertice*)malloc(sizeof(Vertice));

	v->id = 0;
	v->adjacentes = NULL;
	v->valor = valor;

	return v;

}

void insereVertice(Grafo* g, int valor){
	
	Vertice* v = criaVertice(valor);

	if(g->tamanho == 0)
		g->primeiro->prox = v;

	g->tamanho++;
	v->id = g->tamanho;

	g->ultimo->prox = v;
	v->ant = g->ultimo;
	g->ultimo = v;



}

Vertice* encontraVertice(Grafo* g, int v){

	Vertice* v1 = g->primeiro->prox;

	while(v1 != NULL){

		if(v1->id == v)
			return v1;
		v1 = v1->prox;

	}

	return v1;

}

void insereAresta(Grafo* g, int v1, int v2, int peso){

	Vertice* origem = encontraVertice(g, v1);

	if(origem == NULL)
		return;
	inserir(origem->adjacentes, criaItem(), v2, peso);

}

int existeAresta(Grafo* g, int v1, int v2){

	Vertice* origem = encontraVertice(g, v1);

	if(origem == NULL)
		return 0;

	return buscarElemento(origem->adjacentes, v2); 

}

Lista* obtemAdjacentes(Grafo* g, int v){

	Vertice* origem = encontraVertice(g, v);

	if(origem == NULL)
		return NULL;

	return origem->adjacentes;

}

void removeAresta(Grafo* g, int v1, int v2, int peso){

	Vertice* origem = encontraVertice(g, v1);

	if(origem == NULL)
		return;

	removeElemento(origem->adjacentes, v2, peso);

}

void apagaGrafo(Grafo* g){

	Vertice* atual = g->primeiro->prox;
	Vertice* aux;

	while(atual != NULL){

		deletaLista(atual->adjacentes);
		aux = atual;
		atual = atual->prox;
		free(aux);

	}

	free(g);

}

void desenhaGrafo(Grafo* g){

	Vertice* atual = g->primeiro->prox;

	while(atual != NULL){

		printf("%d : %d\n", atual->id, atual->valor);
		atual = atual->prox;

	}

}

Grafo* transposto(Grafo* g){

	// ????????????????

}

