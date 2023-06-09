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
        o->indice = -1;

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
        i->indice = l->tamanho++;


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

Item* buscarElemento(Lista* l, int id){
        if(listaVazia(l))
                return NULL;

        Item* atual = l->primeiro->proximo;

        // f(n) = n + 1 + g(n)
        // f(n) = 2n + 1 = O(n)
        while(atual!=NULL){
                if(id == atual->indice) // g(n) = n
                        return atual;
                atual = atual->proximo;
        }

        return NULL;

        // F(n) = O(n)
}

void imprimeLista(Lista* l){

	if(listaVazia(l)){
		return;
	}

	Item* atual = l->primeiro->proximo;
	while(atual!=NULL){
		printf("%c", atual->id);
		atual = atual->proximo;
	}
	printf("\n");
}

void sol1(Lista* texto, Lista* padrao, FILE* out){
        
        Item* atualT;
        Item* atualP;
        int inicioC = -1;
        int casou = 0;

        atualT = texto->primeiro->proximo;
        atualP = padrao->primeiro->proximo;

        // Enquanto o texto não acabar, continua procurando

        while(atualT != NULL){

                
                if(atualT->id == atualP->id){

                        if(atualP->indice == 0){
                                //Inicio do casamento
                                inicioC = atualT->indice;
                        }
                        atualP = atualP->proximo;
                        if(atualP == NULL){
                                //Chegou ao final do padrão
                                fprintf(out, "S %d\n", inicioC+1);
                                casou = 1;
                                break;
                        }

                } else{
                        //Retorna ao inicio do padrão
                        atualP = padrao->primeiro->proximo;
                        if(inicioC != -1){
                                //Retorna a letra que iniciou o casamento, caso estivesse em um
                                atualT = buscarElemento(texto, inicioC);
                                inicioC = -1;
                        }
                }

                if((inicioC != -1) && (atualT->proximo == NULL)){
                        // Está em um casamento e o texto chegou ao fim
                        atualT = texto->primeiro->proximo;
                } else{
                        atualT = atualT->proximo;
                }
                        
        }

       if(casou == 0){
                //Não houve casamento.
                fprintf(out, "N\n");
       }
    
}


void sol2(Lista* texto, Lista* padrao){
        //Boyer Moore Horspool
}


void sol3(Lista* texto, Lista* padrao){
        // Shift and
}