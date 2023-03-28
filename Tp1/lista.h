
typedef struct item{

                int coord[2];

                struct item *proximo;

                struct item *anterior;


} Item;

typedef struct lista{

                Item *primeiro;
                Item *ultimo;
                Item *ancoras[2];
                int tamanho;

}Lista;

Lista* criaListaVazia(Item*, Item*);
Item* criaItem(int, int);
Item* criaOrigem();
void inserir(Lista*, Item*);
void troca(Lista*, Item*, Item*);
int listaVazia(Lista*);
int* removeElemento(Lista*, int*);
void imprimeLista(Lista*);
Item* buscarElemento(Lista*, int*);
void deletaLista(Lista*);
