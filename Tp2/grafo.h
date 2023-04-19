
typedef struct aresta {

	Nodulo* origem;
	Nodulo* destino;

} Aresta;


typedef struct nodulo {

} Nodulo;


Nodulo* criarNodulo();
void criarAresta(Nodulo*, Nodulo*);
void removerNodulo(Nodulo*);
void destruirGrafo(Nodulo*);
