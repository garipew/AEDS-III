tp3: lista.o main.o
	gcc lista.o main.o -o tp3

lista.o: lista.h lista.c
	gcc -c lista.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp3
