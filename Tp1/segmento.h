#include "lista.h"

typedef struct seg{

    Item* pontoI;
    Item* pontoF;

} Segmento;

Segmento* criarSegmento(Item*, Item*);
int checarIntersecao(Segmento*, Segmento*);
int conectados(Lista*);
