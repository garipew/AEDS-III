tp1:  lista.o segmento.o main.o
	gcc lista.o segmento.o main.o -o tp1

lista.o: lista.h lista.c
	gcc -c lista.c

segmento.o: segmento.h segmento.c
	gcc -c segmento.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp1
