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
        o->salto = -1;

        return o;

        // O(1)

}

Item* criaItem(char id, int salto){

        Item* c = (Item*) malloc(sizeof(Item));

        c->proximo = NULL;
        c->anterior = NULL;

        c->salto = salto;
        c->id = id;

        for(int i = 0; i < 100; i++){
                // Inicia a mascara de bits com 0 em todas as posições.
                c->mascara[i] = 0;
        }


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

Item* buscarId(Lista* l, char id){
        if(listaVazia(l))
                return NULL;

        Item* atual = l->primeiro->proximo;

        // f(n) = n + 1 + g(n)
        // f(n) = 2n + 1 = O(n)
        while(atual!=NULL){
                if(id == atual->id) // g(n) = n
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
                                return;
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

        // Não houve casamento.
        fprintf(out, "N\n");
    
}

Lista* presol2(Lista* p){
        // Pre-processamento da solução 2
        Lista* a = criaListaVazia();
        Item* aux;
        Item* encontrados;

        char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";

        // Maior salto possível para todo alfabeto.
        for(int i = 0; i < 26; i++){
                inserir(a, criaItem(alfabeto[i], p->tamanho));
        }

        /*
        Ajusta salto para letras no padrão para tamanho - indice,
        com exceção da última letra que mantém o valor de salto definido.
        */
        aux = p->primeiro->proximo;
        while(aux != NULL){

                encontrados = buscarId(a, aux->id);
                if(encontrados != NULL){
                        encontrados->salto = (p->tamanho - aux->indice == 1 ? encontrados->salto : p->tamanho - aux->indice -1);
                }

                aux = aux->proximo;
        }


        return a;

}

void sol2(Lista* texto, Lista* padrao, FILE* out){
        
        //Boyer Moore Horspool
        
        Lista* alfabeto = presol2(padrao);
        Item* aux;

        Item* atualPadrao = padrao->ultimo;
        Item* atualTexto = texto->primeiro->proximo;

        for(int j = 0; j < padrao->tamanho-1; j++){
                // Alinhando texto e padrão.
                if(atualTexto->proximo == NULL){
                        atualTexto = texto->primeiro->proximo;
                        continue;
                }
                atualTexto = atualTexto->proximo;
        }

        int p = 0;
        int letras = 0;

        while(atualTexto != NULL){

                

                if(atualTexto->id == atualPadrao->id){

                        if(atualPadrao == padrao->primeiro->proximo){
                                // Casamento.
                                fprintf(out, "S %d\n", atualTexto->indice+1);
                                return;
                        }


                        if(atualTexto->anterior == texto->primeiro){
                                atualTexto = texto->ultimo;
                        } else{
                                atualTexto = atualTexto->anterior;
                        }

                        letras++;

                        atualPadrao = atualPadrao->anterior;
                } else{
                        // Letras diferentes.
                        atualPadrao = padrao->ultimo;
                        
                        aux = buscarId(alfabeto, atualTexto->id);

                        for(int k = 0; k < letras; k++){
                                // Retorna à letra do texto que iniciou o casamento.
                                if(atualTexto->proximo == NULL){
                                        atualTexto = texto->primeiro->proximo;
                                        continue;
                                }
                                atualTexto = atualTexto->proximo;
                        }
                        
                        for(int i = 0; i < aux->salto; i++){
                                // Realiza o salto e alinha texto e padrão.

                                if(p > 0){
                                        p++;
                                }


                                if(atualTexto == NULL){
                                        // Chegou ao fim e o padrao todo já passou do fim ao inicio.
                                        break;
                                }


                                if((atualTexto->proximo == NULL) && (p < padrao->tamanho)){
                                        // Ao chegar ao fim do texto, volta ao início p letras,
                                        // nunca permitindo que o padrão inteiro retorne
                                        atualTexto = texto->primeiro->proximo;
                                        if(p == 0){
                                                p = 1;
                                        }
                                        continue;

                                }

                                atualTexto = atualTexto->proximo;
                        
                        }
                        
                        letras = 0;

                }


        }

        // Não há casamento.
        fprintf(out, "N\n");
  
}

Lista* presol3(Lista* texto, Lista* padrao){

        Lista* a = criaListaVazia();
        Item* atual;
        Item* aux;

        char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";

        // Cria a mascara de bits para todo o alfabeto.
        for(int i = 0; i < 26; i++){
                inserir(a, criaItem(alfabeto[i], -1));
        }

        atual = padrao->primeiro->proximo;

        while(atual != NULL){
                aux = buscarId(a, atual->id);
                aux->mascara[atual->indice]++;
                atual = atual->proximo;
        }

        return a;

}


void sol3(Lista* texto, Lista* padrao, FILE* out){
        
        // Shift and

        Lista* alfabeto = presol3(texto, padrao);
        int r[padrao->tamanho];

        Item* atualTexto = texto->primeiro->proximo;
        Item* aux;

        int continua = 0;
        int passou = 0;
        int inicioC;

        for(int i = 0; i < padrao->tamanho; i++){
                r[i] = 0;
        }

        while(atualTexto != NULL){
                
                if(passou > 0){
                        // Contabiliza letras que chegaram ao fim do texto e retornaram ao inicio.
                        passou++;
                }
                if(passou >= padrao->tamanho){
                        /*
                        Quando passou >= padrao->tamanho a busca começa a se repetir,
                        portanto, não há casamento neste texto 
                        */
                        break;
                }
                
                aux = buscarId(alfabeto, atualTexto->id);


                // Shift
                for(int j = 1; j < padrao->tamanho; j++){
                        r[padrao->tamanho - j] = r[padrao->tamanho - j - 1];
                }

                r[0] = 1;

                for(int k = 0; k < padrao->tamanho; k++){
                        // And
                        r[k] = r[k] && aux->mascara[k];
                }

                for(int z = 0; z < padrao->tamanho; z++){
                        continua += r[z]; 
                }

                if(r[padrao->tamanho - 1] == 1){
                        // Casamento
                        inicioC = atualTexto->indice - (padrao->tamanho - passou);
                        while(inicioC < 0){
                                inicioC += texto->tamanho;
                        }
                        fprintf(out, "S %d\n", inicioC);
                        return;
                }

                if((continua >= 1) && atualTexto->proximo == NULL){
                        /*
                        Chegou ao fim do texto e há um possível casamento,
                        retorna ao inicio do texto.
                        */
                        atualTexto = texto->primeiro->proximo;
                        passou = 1;
                } else{
                        atualTexto = atualTexto->proximo;
                }
        }
        
        // Não há casamento.
        fprintf(out, "N\n");

        
}

void sol(Lista* texto, Lista* padrao, FILE* out, int solucao){

        // Alterna entre possíveis soluções.
        switch(solucao){

                case 1:
                        sol1(texto, padrao, out);
                        break;
                case 2: 
                        sol2(texto, padrao, out);
                        break;
                case 3: 
                        sol3(texto, padrao, out);

        }

}

void casosTeste(int T, FILE* entrada, FILE* saida, int escolhida){

        char c;

        Lista* texto;
        Lista* padrao;

        for(int i = 0; i < T; i++){
                padrao = criaListaVazia();
                texto = criaListaVazia();

                // Coletando padrão e texto
                while((c = getc(entrada)) != ' '){
                        inserir(padrao, criaItem(c, -1));
                }
                while((c = getc(entrada)) != EOF){
                        if(c == '\n'){
                                break;
                        }
                        inserir(texto, criaItem(c, -1));
                }


                // Executa solução.
                sol(texto, padrao, saida, escolhida);

                deletaLista(padrao);
                deletaLista(texto);
        
        }

}