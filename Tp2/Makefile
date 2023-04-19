tp2: grafo.o main.o
	gcc grafo.o main.o -o tp2

grafo.o: grafo.h grafo.c
	gcc -c grafo.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp2
