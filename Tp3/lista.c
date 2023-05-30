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
        
        o->id = ' ';

        return o;

        // O(1)

}

Item* criaItem(char id){

        Item* c = (Item*) malloc(sizeof(Item));

        c->proximo = NULL;
        c->anterior = NULL;

        c->id = id;

        return c;

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


}

void atualiza(Lista* l, Item* j){

         if(j->proximo==NULL){
                 l->ultimo = j;
         } else{
                 j->proximo->anterior = j;
         }
        
        j->anterior->proximo = j;

        // F(n) = O(1)
}


int listaVazia(Lista* l){

        if(l == NULL)
                return 1;

        if(l->tamanho == 0)
                return 1;
        return 0;

        // O(1)

}

void removeElemento(Lista* l, char ident){
        if(listaVazia(l))
                return;

        //int* c;
        Item* atual = l->primeiro;
        Item* aux;

        // f(n) = 3n + 1 = O(n)
        while(atual->proximo != NULL){

                if(atual->proximo->id == ident){
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
                removeElemento(l, l->ultimo->id); // g(n) = O(n) * n = O(n²)
        }

        Item* origem = l->primeiro;
        free(origem);
        free(l);

        // F(n) = O(n²)

}

int buscarElemento(Lista* l, char id){
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

void imprimeLista(Lista* l){

	if(listaVazia(l)){
		return;
	}

	Item* atual = l->primeiro->proximo;
	while(atual!=NULL){
		if(atual->proximo!=NULL){
			printf("%c, ", atual->id);
			atual = atual->proximo;
		}
		else{
			printf("%c", atual->id);
			atual = atual->proximo;
		}
	}
	printf("\n");
}