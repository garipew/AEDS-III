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
	v->prox = NULL;

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
	Vertice* aux = atual->prox;

	while(aux != NULL){

		if(aux->adjacentes != NULL)
			deletaLista(aux->adjacentes);

		atual->prox = atual->prox->prox;
		if(aux->prox == NULL)
			g->ultimo = atual;

		g->tamanho--;
		if(g->tamanho == 0)
			g->ultimo = g->primeiro;
		if(aux != NULL){
			free(aux);
		}

		aux = aux->prox;

	}

	free(g);
	// fixed?
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


int solucao3(Grafo* g, int C){

	Fila* f = criaFila();
	Vertice* atual = g->primeiro->prox;
	Item* aux;
	Vertice* cima;
	Vertice* esq;
	Vertice* melhor;
	int baixo, direita, diagonal;
	int vida = 0;

	if(atual->valor <= 0){
		atual->hpMin = (-1*atual->valor) + 1;
	} else{
		atual->hpMin = 1;
	}

	atual->hpFinal = 1;

	baixo = atual->id + C;
	direita = atual->id + 1;
	diagonal = baixo + 1;



	do{
		/*
		Enfilera elementos a direita, baixo e diagonal.
		Encontra a vida necessária para chegar na direita e no de baixo
		e escolhe o menor destes para encontrar o minimo para chegar na diagonal.
		*/

		baixo = atual->id + C;
		direita = atual->id + 1;
		diagonal = baixo + 1 * (atual->id%C != 0);


		if((direita-1)/C == (atual->id-1)/C){
			if(!busca(direita, f)){
				enfilera(direita, 1, f);
			}
		}

		if(baixo <= g->tamanho){
			if(!busca(baixo, f)){
				enfilera(baixo, 2, f);
			}
		}

		if(diagonal <= g->tamanho && diagonal > 0){
			if(!busca(diagonal, f)){
				enfilera(diagonal, 3, f);
			}
		}

		aux = desenfilera(f);
		atual = encontraVertice(g, aux->destino);

		switch(aux->peso){
			
			case 1: 
				/*
			 	Direita, neste caso o mínimo depende apenas do vértice à esquerda.
				Entra nessa condição apenas para os vértices da primeira linha da matriz
				*/

				esq = encontraVertice(g, aux->destino - 1);
				atual->hpFinal = esq->hpFinal + atual->valor;
				atual->hpMin = esq->hpMin;
				if(atual->hpFinal <= 0){
					/*
					hpMin += (hpFinal + valor) é o mínimo necessário para atravessar este vértice, tendo em vista que
					hpMin - (hpFinal + valor) = 1.
					Caso hpFinal + valor = 0, não funciona muito bem, visto que
					0 = -0 e assim não haveria incremento em hpMin.
					Por isso o incremento é dado por 
					hpMin += (hpFinal + valor) + (hpFinal + valor == 0)
					O último termo é 1 quando o primeiro termo do incremento é 0, sendo assim, sempre que necessário há incremento.
					*/

					atual->hpMin += (-1 * atual->hpFinal) + (atual->hpFinal == 0);
					atual->hpFinal = 1;
				}
				break;
			case 2:
				/*
				Baixo, mínimo depende apenas do vértice em cima.
				Entra nessa condição apenas para os vértices da primeira coluna da matriz.
				*/
				cima = encontraVertice(g, aux->destino - C);
				atual->hpFinal = cima->hpFinal + atual->valor;
				atual->hpMin = cima->hpMin;
				if(atual->hpFinal <= 0){
					atual->hpMin += (-1 * atual->hpFinal) + (atual->hpFinal == 0);
					atual->hpFinal = 1;
				}
				break;
			case 3:
				/*
				Diagonal, mínimo é dado pelo menor custo entre o vértice da esquerda e o vértice de cima.
				Entra nessa condição para a maior parte dos vértices.
				*/
				cima = encontraVertice(g, aux->destino - C);
				esq = encontraVertice(g, aux->destino - 1);

				/*
				O vértice preferido é aquele com maior vida, caso ambos sejam iguais a 1, significa que
				potencialmente houve incremento em hpMin deles, sendo assim, o desejável é o com o menor hpMin possível.
				*/
				if(esq->hpFinal > cima->hpFinal){
					melhor = esq;
				} else if(cima->hpFinal > esq->hpFinal){
					melhor = cima;
				} else{
					melhor = (esq->hpMin <= cima->hpMin ? esq : cima);
				}
				atual->hpFinal = melhor->hpFinal + atual->valor;
				atual->hpMin = melhor->hpMin;
				if(atual->hpFinal <= 0){
					atual->hpMin += (-1 * atual->hpFinal) + (atual->hpFinal == 0);
					atual->hpFinal = 1;
				}
				break;

		}


	} while(!filaVazia(f));

	deletaFila(f);
	
	/*
	Dessa forma, todos os vértices do grafo são percorridos uma única vez,
	e o resultado obtido é o mínimo.
	*/

	return g->ultimo->hpMin;

}

void solucao(Grafo* g, int solucao, int C, FILE* s){

	// Alterna entre as possíveis soluções.

	int hp = 0;

	if(solucao == 1){
		/*
		Utiliza solucao1 para encontrar um hpFinal aproximado a fim de 
		otimizar a execução da solucao2.
		*/
		g->ultimo->hpFinal = solucao1(g);
		solucao2(g, g->primeiro->prox, 0, -1);
		hp = g->ultimo->hpFinal;
	} else if(solucao == 2){
		hp = solucao3(g, C);
	}

	fprintf(s, "%d\n", hp);
}