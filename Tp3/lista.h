
typedef struct item{

    char id;
    int indice;

    struct item *proximo;

    struct item *anterior;


} Item;

typedef struct lista{

    Item *primeiro;
    Item *ultimo;
    int tamanho;

}Lista;

Lista* criaListaVazia();
Item* criaItem(char);
Item* criaOrigem();
void inserir(Lista*, Item*);
int listaVazia(Lista*);
void removeElemento(Lista*, char);
int buscarElemento(Lista*, char);
void deletaLista(Lista*);
void imprimeLista(Lista*);