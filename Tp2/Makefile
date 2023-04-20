tp2: lista.o grafo.o main.o
	gcc lista.o grafo.o main.o -o tp2

lista.o: lista.h lista.c
	gcc -c lista.c

grafo.o: grafo.h grafo.c
	gcc -c grafo.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp2
