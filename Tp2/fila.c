#include "fila.h"
#include <stdio.h>
#include <stdlib.h>


Fila* criaFila(){

	Fila* f = (Fila*)malloc(sizeof(Fila));
	
	Item* orig = criaOrigem();

	f->primeiro = orig;
	f->ultimo = orig;

	f->tamanho = 0;
	
	return f;

}


int filaVazia(Fila* f){

	if(f->tamanho <= 0)
		return 1;
	return 0;

}


void enfilera(int id, int dig, Fila* f){

	Item* i = criaItem();

	i->destino = id;
	i->peso = dig;

	f->ultimo->proximo = i;
	f->ultimo = i;
	f->tamanho++;

}


Item* desenfilera(Fila* f){

	if(filaVazia(f))
		return NULL;


	Item* aux = f->primeiro->proximo;
	if(aux == f->ultimo)
		f->ultimo = f->primeiro;

	f->primeiro->proximo = aux->proximo;
	f->tamanho--;

	return aux;

}

void imprimeFila(Fila* f){

	char tipo[] = {'d', 'b', 'D'};

	if(filaVazia(f))
		return;

	Item* aux = f->primeiro->proximo;

	printf("=====\n");
	while(aux != NULL){
		
		printf("%d%c ", aux->destino, tipo[aux->peso-1]);
		aux = aux->proximo;

	}

	printf("\n=====\n");


}


int busca(int id, Fila* f){

	if(filaVazia(f)){
		return 0;
	}

	Item* item = f->primeiro->proximo;

	while(item != NULL){

		if(item->destino == id){
			return 1;

		}
		item = item->proximo;
	}

	return 0;

}



void deletaFila(Fila* f){
	
	Item* aux;

	while(!filaVazia(f)){
	
		aux = desenfilera(f);
		free(aux);
	
	}

	free(f);

}
