#include "lista.h"

typedef struct fila{

	Item* primeiro;
	Item* ultimo;
	int tamanho;

} Fila;

Fila* criaFila();
void enfilera(int, int, Fila*);
void imprimeFila(Fila*);
int busca(int, Fila*);
Item* desenfilera(Fila*);
int filaVazia(Fila*);
void deletaFila(Fila*);
