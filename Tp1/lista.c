#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista* criaListaVazia(Item* ancoraA, Item* ancoraB){
        Lista* l = (Lista*)malloc(sizeof(Lista));
        Item* origem = criaOrigem();

        l->primeiro = origem;
        l->ultimo = origem;
        l->tamanho = 0;
        l->primeiro->proximo = NULL;
        l->ultimo->anterior = NULL;
        l->ancoras[0] = ancoraA;
        l->ancoras[1] = ancoraB;


        return l;

        // O(1)

}

Item* criaOrigem(){

        Item* o = (Item*) malloc(sizeof(Item));
        o->coord[0] = 0;
        o->coord[1] = 0;
        o->id = -1;

        return o;

        // O(1)

}

Item* criaItem(int x, int y, int indice){

        Item* c = (Item*) malloc(sizeof(Item));

        c->proximo = NULL;
        c->anterior = NULL;


        c->coord[0] = x;
        c->coord[1] = y;
        c->id = indice;

        return c;

}

void insertionSort(Lista* l){
	
	Item* i = l->primeiro->proximo;
	Item* j;

        int desempate = ((l->ancoras[0]->coord[0] + l->ancoras[1]->coord[0]))/2;

	while(i != l->ultimo->proximo){

		j = i;
		while(j != l->primeiro->proximo){
			// O código abaixo tem como função ordenar os pontos do campo do menor y
			// para o maior, sendo o critério de desempate o ponto mais proximo da média 
			// do X das duas âncoras.
				if(j->coord[1] != j->anterior->coord[1]){
					if(j->coord[1] < j->anterior->coord[1]){
						troca(l, j, j->anterior);
						continue;
					}
				} else{

                                        if(abs(j->coord[0] - desempate) > abs(j->anterior->coord[0] - desempate)){
                                                troca(l, j, j->anterior);
                                        }

				}	
			j = j->anterior;			
		}
		i = i->proximo;

	}

}

void inserir(Lista* l, Item* i){

        if(listaVazia(l)){
                l->primeiro->proximo = i;
        }

        i->anterior = l->ultimo;
        i->proximo = NULL;
        l->ultimo->proximo = i;
        l->ultimo = i;
        l->tamanho++;
        if(i->id == 0){
                i->id = l->tamanho;
        }

        insertionSort(l);

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

        if(l->tamanho == 0)
                return 1;
        return 0;

        // O(1)

}

int compararPontos(Item *p, int a){

        if(a == p->id)
                return 1;
        return 0;

}

void removeElemento(Lista* l, int ident){
        if(listaVazia(l))
                return;

        //int* c;
        Item* atual = l->primeiro;
        Item* aux;

        // f(n) = 3n + 1 = O(n)
        while(atual->proximo != NULL){

                if(compararPontos(atual->proximo, ident)){
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

        free(l->ancoras[0]);
        free(l->ancoras[1]);
        
        for(int i = 0; i<tamanho; i++){
                removeElemento(l, l->ultimo->id); // g(n) = O(n) * n = O(n²)
        }

        Item* origem = l->primeiro;
        free(origem);
        free(l);

        // F(n) = O(n²)

}

void imprimeLista(Lista* l){

        if(listaVazia(l)){
                printf("Lista Vazia!\n");
                return;
        }

        /*
        for(int i = 0; i < 2; i++){
                printf(ANSI_COLOR_RED "(%d ;%d)\n", l->ancoras[i]->coord[0], l->ancoras[i]->coord[1]);
        }
        */


        Item* atual = l->primeiro->proximo;
        // f(n) = n + 1
        while(atual!=NULL){
                printf("(%d; %d)\n", atual->coord[0], atual->coord[1]);
                atual = atual->proximo;
        }

        // F(n) = O(n)
}

int buscarElemento(Lista* l, int id){
        if(listaVazia(l))
                return 0;

        Item* atual = l->primeiro->proximo;

        // f(n) = n + 1 + g(n)
        // f(n) = 2n + 1 = O(n)
        while(atual!=NULL){
                if(id == atual->id) // g(n) = n
                        return 1;
                atual = atual->proximo;
        }

        return 0;

        // F(n) = O(n)
}

Item* clonarItem(Item* a){

        Item* clone = criaItem(a->coord[0], a->coord[1], a->id);

        return clone;

}