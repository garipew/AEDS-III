#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista* criaListaVazia(){
        Lista* l = (Lista*)malloc(sizeof(Lista));
        Item* origem = criaOrigem();

        l->primeiro = origem;
        l->ultimo = origem;
        l->tamanho = 0;
        l->primeiro->proximo = NULL;
        l->ultimo->anterior = NULL;


        return l;

        // O(1)

}

Item* criaOrigem(){

        Item* o = (Item*) malloc(sizeof(Item));
        
        o->destino = 0;
        o->peso = -1;

        return o;

        // O(1)

}

Item* criaItem(){

        Item* c = (Item*) malloc(sizeof(Item));

        c->proximo = NULL;
        c->anterior = NULL;

        c->destino = 0;
        c->peso = 0;

        return c;

}

void inserir(Lista* l, Item* i, int destino, int peso){

        if(listaVazia(l)){
                l->primeiro->proximo = i;
        }

        i->anterior = l->ultimo;
        i->proximo = NULL;
        l->ultimo->proximo = i;
        l->ultimo = i;
        l->tamanho++;

        i->peso = peso;
        i->destino = destino;



}

void atualiza(Lista* l, Item* j){

         if(j->proximo==NULL){
                 l->ultimo = j;
         } else{
                 j->proximo->anterior = j;
         }
         //if(j->anterior == l->primeiro){
           //      l->primeiro->proximo = j;
         //} else{
                 j->anterior->proximo = j;
         //}

         // F(n) = O(1)
}

void trocaLateral(Item* esq, Item* dir){

        Item* auxp = dir->proximo;

        dir->anterior = esq->anterior;
        dir->proximo = esq;
        esq->anterior = dir;
        esq->proximo = auxp;

        // F(n) = O(1)

}


void troca(Lista* l, Item* i, Item* j){

        if(i == NULL || j == NULL)
                return;


        if(i->anterior == j){

                trocaLateral(j, i);

                // h(n) = O(1)
        }else if(j->anterior == i){

                trocaLateral(i, j);

                // h(n)
        } else{

	        Item* aux = i->anterior;
	        Item* auxp = i->proximo;

	        i->proximo = j->proximo;
	        i->anterior = j->anterior;
	        j->anterior = aux;
	        j->proximo = auxp;

    	}	

        atualiza(l, i);
        atualiza(l, j);
        // h(n)
        //
        // F(n) = h(n)
        // F(n) = O(1) = O(1)

}


int listaVazia(Lista* l){

        if(l == NULL)
                return 1;

        if(l->tamanho == 0)
                return 1;
        return 0;

        // O(1)

}

int compararPontos(Item *p, int destino, int peso){

        if(destino == p->destino && peso == p->peso)
                return 1;
        return 0;

}

void removeElemento(Lista* l, int ident, int peso){
        if(listaVazia(l))
                return;

        //int* c;
        Item* atual = l->primeiro;
        Item* aux;

        // f(n) = 3n + 1 = O(n)
        while(atual->proximo != NULL){

                if(compararPontos(atual->proximo, ident, peso)){
                        aux = atual->proximo;
                        atual->proximo = atual->proximo->proximo;
                        if(aux->proximo == NULL){
                                l->ultimo = atual;
                        }
                        l->tamanho--;
                        if(l->tamanho == 0){
                                l->ultimo = l->primeiro;
                        }

                        //c = aux->coord;
                        if(aux!=NULL)
                                free(aux);
                        return;
                }
                atual = atual->proximo;

        }

        // F(n) = O(n)

}

void deletaLista(Lista* l){


        int tamanho = l->tamanho;

        // f(n) = n + 1 + g(n)
        // f(n) = O(n²)
        
        for(int i = 0; i<tamanho; i++){
                removeElemento(l, l->ultimo->destino, l->ultimo->peso); // g(n) = O(n) * n = O(n²)
        }

        Item* origem = l->primeiro;
        free(origem);
        free(l);

        // F(n) = O(n²)

}

int buscarElemento(Lista* l, int destino){
        if(listaVazia(l))
                return 0;

        Item* atual = l->primeiro->proximo;

        // f(n) = n + 1 + g(n)
        // f(n) = 2n + 1 = O(n)
        while(atual!=NULL){
                if(destino == atual->destino) // g(n) = n
                        return 1;
                atual = atual->proximo;
        }

        return 0;

        // F(n) = O(n)
}

void imprimeLista(Lista* l){

	if(listaVazia(l)){
		return;
	}

	Item* atual = l->primeiro->proximo;
	while(atual!=NULL){
		if(atual->proximo!=NULL){
			printf("v%d : %d, ", atual->destino, atual->peso);
			atual = atual->proximo;
		}
		else{
			printf("v%d : %d", atual->destino, atual->peso);
			atual = atual->proximo;
		}
	}
	printf("\n");
}