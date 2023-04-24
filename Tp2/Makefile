tp2: lista.o grafoV2.o main.o
	gcc lista.o grafoV2.o main.o -o tp2

lista.o: lista.h lista.c
	gcc -c lista.c

grafoV2.o: grafoV2.h grafoV2.c
	gcc -c grafoV2.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o tp2
