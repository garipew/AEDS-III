#include "grafoV2.h"
#include <stdlib.h>
#include <stdio.h>


Vertice* criaVertice(int valor){

	Vertice* v = (Vertice*)malloc(sizeof(Vertice));

	v->id = 0;
	v->adjacentes = NULL;
	v->valor = valor;

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

	// Adiciona na lista de adjacentes de v1 um item com o id de v2.

	Vertice* origem = encontraVertice(g, v1);
	if(origem == NULL)
		return;
	if(origem->adjacentes == NULL)
		origem->adjacentes = criaListaVazia();
	
	inserir(origem->adjacentes, criaItem(), v2, peso);

}

int existeAresta(Grafo* g, int v1, int v2){

	// Busca v2 na lista de adjacentes de v1, retorna 1 caso encontre e 0 caso contrário.

	Vertice* origem = encontraVertice(g, v1);

	if(origem == NULL)
		return 0;

	return buscarElemento(origem->adjacentes, v2); 

}

Lista* obtemAdjacentes(Grafo* g, int v){

	// Retorna a lista de adjacentes de um vertice qualquer, baseado em seu id.
	Vertice* origem = encontraVertice(g, v);

	if(origem == NULL)
		return NULL;

	return origem->adjacentes;

}

void removeAresta(Grafo* g, int v1, int v2, int peso){

	// Remove uma aresta especificada do grafo
	Vertice* origem = encontraVertice(g, v1);

	if(origem == NULL)
		return;

	removeElemento(origem->adjacentes, v2, peso);

}

void apagaGrafo(Grafo* g){
	/*
	Percorre o grafo removendo as listas de adjacentes,
	os vértices e por fim liberando o espaço alocado.
	*/


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

	// printa o id dos vertices e seus adjacentes

	Vertice* atual = g->primeiro->prox;

	while(atual != NULL){

		printf("v%d\n", atual->id);
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

			// Insere arestas para direita em todos os elementos, exceto nos da última coluna da grid.
            if(contador%C != 0)
                insereAresta(g, contador, contador+1, 1);
			// Insere arestas para baixo em todos os elementos, exceto nos da última linha.
            if(contador <= ((R*C)-C))
	            insereAresta(g, contador, contador+C, 1);

		}
            
    }

}

int solucao1(Grafo* g){

/*
 Percorre o grafo indo sempre para posição mais promissora
  (de maior valor) no momento, sem considerar passos anteriores.
*/

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
			/*
			Caso o vértice atual tenha 2 adjacentes, o proximo vértice
			percorrido será o de maior valor.
			*/

			aux2 = encontraVertice(g, adj->proximo->destino);
			atual = (aux->valor >= aux2->valor ? aux : aux2);

		}else{
			atual = aux;
		}

		hpAtual += atual->valor;

		if(hpAtual+hpTotal <= 0){
			/*
			Dessa forma, há a garantia que hpTotal sempre será o menor inteiro maior que
			hpAtual, fazendo com que a soma de ambos seja maior que 0.
			*/
			hpTotal = ((-1*hpAtual)+1);	
		}else if(hpTotal > atual->valor && atual->valor > 0){
			/*
			Ao somá-los, o novo numero permanece maior que zero, como o buscado é o menor hpTotal possível,
			o valor atual é subtraído de hpTotal, dessa forma, hpTotal permanece maior que zero e é menor agora.
			*/
			hpTotal-= atual->valor;
		}

		aux = NULL;
		aux2 = NULL;
	
	}

	if(hpTotal == 0)
		hpTotal++;
	// O minimo necessário é 1.

	return hpTotal;

}

void solucao2(Grafo* g, Vertice* o, int hp, int hpMin){

/*
solucao2() percorre todos os possíveis caminhos do grafo
e retorna o maior valor possivel da soma dos vetores do caminho	

*/

	int max = hp+o->valor;
	if(max < hpMin){
		max = hpMin;
	}

	/*
	max representa a soma total de vida até o momento,
	caso seja menor que o minimo necessário para alcançar
	tal ponto, é substituida por esse minimo.
	
	*/

	int min = hpMin;
	/*
	em primeiro momento o minimo para alcançar um ponto permance igual,
	se altera apenas caso a soma de vida seja um valor negativo.
	*/

	if(min >= g->ultimo->hpFinal){
		/*
		caso o minimo de hp necessario no vertice atual seja
		maior ou igual ao hpFinal encontrado previamente por outro caminho,
		este caminho não é promissor.
		*/
		return;
	}


	if(o->id == g->ultimo->id){

		/*
		O valor buscado para o->hpFinal é o número mais próximo de 1 possível,
		sendo assim, se hpFinal < 0 então será substituido por max apenas se max >= hpFinal.
		Se hpFinal > 0, será substituído por max somente se 0 < max < hpFinal.
		*/
		
		if(o->hpFinal < 0 && max >= o->hpFinal){
			o->hpFinal = max;
		} else if(o->hpFinal >= 0 && max < o->hpFinal){
			o->hpFinal = max;
		}

		if(min < 0){
			/*
			Caso min < 0, significa que não há nenhuma perda de hp
			nesse caminho, sendo assim, o hp necessario é o menor possível,
			sendo ele 1.
			*/
			o->hpFinal = 1;
		}

		return;

	}

	if(g->ultimo->hpFinal == 1){
		/*
		caso hpFinal = 1 o melhor caminho possível já foi
		encontrado, sendo assim, não é preciso buscar melhores
		alternativas.
		*/
		return;
	}

	if(max < 0){
		/*
		Atualiza o minimo de vida necessário para este ponto.
		*/
		min = (-1*max) + 1;
	}
	

	/*
	chamadas recursivas para percorrer todos
	os possíveis caminhos até o objetivo
	*/
	Vertice* direita = encontraVertice(g, o->adjacentes->primeiro->proximo->destino);
	Vertice* baixo = NULL;
	solucao2(g, direita, max, min);
	if(o->adjacentes->tamanho == 2){
		baixo = encontraVertice(g, o->adjacentes->primeiro->proximo->proximo->destino);
		solucao2(g, baixo, max, min);
	}

	return;

}

void solucao(Grafo* g, int solucao, FILE* s){

	// Alterna entre as possíveis soluções.

	int hp = 0;

	if(solucao == 1)
		hp = solucao1(g);
	else if(solucao == 2){
		/*
		Utiliza solucao1 para encontrar um hpFinal aproximado a fim de 
		otimizar a execução da solucao2.
		*/
		g->ultimo->hpFinal = solucao1(g);
		solucao2(g, g->primeiro->prox, 0, -1);
		hp = g->ultimo->hpFinal;
	}

	fprintf(s, "%d\n", hp);
}