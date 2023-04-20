
typedef struct item{

    int destino;
    int peso;

    struct item *proximo;

    struct item *anterior;


} Item;

typedef struct lista{

    Item *primeiro;
    Item *ultimo;
    int tamanho;

}Lista;

Lista* criaListaVazia(Item*, Item*);
Item* criaItem();
Item* criaOrigem();
void inserir(Lista*, Item*, int, int);
void troca(Lista*, Item*, Item*);
int listaVazia(Lista*);
void removeElemento(Lista*, int);
int buscarElemento(Lista*, int);
void deletaLista(Lista*);
Item* clonarItem(Item*);
