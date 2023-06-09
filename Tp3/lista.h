#include <stdio.h>

typedef struct item{

    char id;
    int indice;
    int salto;
    int mascara[100];

    struct item *proximo;

    struct item *anterior;


} Item;

typedef struct lista{

    Item *primeiro;
    Item *ultimo;
    int tamanho;

}Lista;

Lista* criaListaVazia();
Item* criaItem(char, int);
Item* criaOrigem();
void inserir(Lista*, Item*);
int listaVazia(Lista*);
void removeElemento(Lista*, char);
Item* buscarElemento(Lista*, int);
void deletaLista(Lista*);
void imprimeLista(Lista*);
void sol(Lista*, Lista*, FILE*, int);
void casosTeste(int, FILE*, FILE*, int);