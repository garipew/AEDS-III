#include "grafoV2.h"
#include <stdlib.h>
#include <stdio.h>


Vertice* criaVertice(int valor){

	Vertice* v = (Vertice*)malloc(sizeof(Vertice));

	v->id = 0;
	v->adjacentes = NULL;
	v->valor = valor;
	v->peso = 1000000000;
	v->antecessor = NULL;

	return v;

}

Grafo* criaGrafo(){

	Grafo* g = (Grafo*)malloc(sizeof(Grafo));
	Vertice* origem = criaVertice(0);
	g->tamanho = 0;

	g->primeiro = origem;
	g->ultimo = origem;
	
	return g;

}


void insereVertice(Grafo* g, int valor){
	
	Vertice* v = criaVertice(valor);

	if(g->tamanho == 0)
		g->primeiro->prox = v;


	g->ultimo->prox = v;
	v->ant = g->ultimo;
	g->ultimo = v;

	g->tamanho++;
	v->id = g->tamanho;


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
	if(origem->adjacentes == NULL)
		origem->adjacentes = criaListaVazia();
	
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

	Vertice* atual = g->primeiro;
	Vertice* aux;

	while(atual->prox != NULL){
		
		aux = atual->prox;
		if(aux->adjacentes != NULL)
			deletaLista(aux->adjacentes);

		atual->prox = atual->prox->prox;
		if(aux->prox == NULL)
			g->ultimo = atual;

		g->tamanho--;
		if(g->tamanho == 0)
			g->ultimo = g->primeiro;
		if(aux != NULL)
			free(aux);

		atual = atual->prox;

	}

	free(g);

}

void desenhaGrafo(Grafo* g){

	Vertice* atual = g->primeiro->prox;

	while(atual != NULL){

		printf("v%d = %d\n", atual->id, atual->valor);
		if(atual->adjacentes != NULL)
			imprimeLista(atual->adjacentes);
		atual = atual->prox;

	}

}


void coletaDados(Grafo* g, int R, int C, FILE* e){

/*
	insere todos os valores da grid no grafo,
	incluindo as arestas dos possiveis caminhos a serem percorridos.
*/	

	int contador = 0;
	int valor;

	while(contador < R*C){

        if(fscanf(e, "%d", &valor) == 1){

            insereVertice(g, valor);
            contador++;

            if(contador%C != 0)
                insereAresta(g, contador, contador+1, 0);
            if(contador <= ((R*C)-C))
	            insereAresta(g, contador, contador+C, 0);


		}
            
    }

}

int solucao1(Grafo* g){

	int hpAtual = 0;
	int hpTotal = 0;
	Vertice* atual = g->primeiro->prox;

	Item* adj;
	Vertice* aux;
	Vertice* aux2;

	while(atual != g->ultimo){

		adj = atual->adjacentes->primeiro->proximo;
		aux = encontraVertice(g, adj->destino);


		if(atual->adjacentes->tamanho == 2){

			aux2 = encontraVertice(g, adj->proximo->destino);
			atual = (aux->valor >= aux2->valor ? aux : aux2);

		}else{
			atual = aux;
		}

		hpAtual += atual->valor;

		if(hpAtual+hpTotal <= 0){
			hpTotal = ((-1*hpAtual)+1);	
		}else if(hpTotal > atual->valor && atual->valor > 0){
			hpTotal-= atual->valor;
		}

		aux = NULL;
		aux2 = NULL;
	
	}

	if(hpTotal == 0)
		hpTotal++;
	
	//fprintf(s, "%d\n", hpTotal);
	return hpTotal;

}

void atualizaPeso(Grafo* g){
	
	// ?

}

int solucao2(Grafo* g){

	//dijkstra

	Vertice* atual = g->primeiro->prox;
	atual->peso = 0;
	Lista* adj;
	Item* itemAux;
	Vertice* aux;
	Vertice* prox;

	while(atual != g->ultimo){

		adj = atual->adjacentes;
		itemAux = adj->primeiro->proximo;

		prox = encontraVertice(g, itemAux->destino);

		while(itemAux != NULL){
			
			aux = encontraVertice(g, itemAux->destino);


			if(aux->peso > itemAux->peso + atual->peso){
				
				aux->peso = itemAux->peso + atual->peso;
				aux->antecessor = atual;

			}

			itemAux = itemAux->proximo;


		}

		atual = (prox->peso <= aux->peso ? prox : aux);

	}
	
	return g->ultimo->peso;

}

void solucao(Grafo* g, int solucao, FILE* s){

	int hp;

	if(solucao == 1)
		hp = solucao1(g);
	else if(solucao == 2){
		hp = solucao2(g);
		if(hp == 0){
			hp++;
		}
	}

	fprintf(s, "%d\n", hp);
}