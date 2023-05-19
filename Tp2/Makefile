tp2: fila.o lista.o grafoV2.o main.o 
	gcc fila.o lista.o grafoV2.o main.o -o tp2

fila.o: fila.h fila.c
	gcc -c fila.c

lista.o: lista.h lista.c
	gcc -c lista.c

grafoV2.o: grafoV2.h grafoV2.c
	gcc -c grafoV2.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp2
