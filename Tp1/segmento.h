#include "lista.h"

typedef struct seg{

    Item* pontoI;
    Item* pontoF;

} Segmento;

Segmento* criarSegmento(Item*, Item*);
int checarInterseção(Segmento*, Segmento*);
int conectados(Lista*);
