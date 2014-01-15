CC = gcc
CFLAGS = -g -c -Wall
LIB1 = -lm
LIB2 = `allegro-config --libs`
principal.saida: estruturas.o funcoes.o arquivo.o main.o
	$(CC) -g -Wall estruturas.o funcoes.o arquivo.o main.o -o main.saida $(LIB1) $(LIB2)

main.o: main.c main.h
	$(CC) $(CFLAGS) -o main.o main.c

arquivo.o: arquivo.c arquivo.h
	$(CC) $(CFLAGS) -o arquivo.o arquivo.c
        
funcoes.o: funcoes.c funcoes.h
	$(CC) $(CFLAGS) -o funcoes.o funcoes.c

estruturas.o: estruturas.c estruturas.h
	$(CC) $(CFLAGS) -o estruturas.o estruturas.c
        	
r: principal.saida
	./main.saida
cls:
	\rm -rf *.o *.saida *.c~ *.h~ Makefile~ *gz |clear

pack:
	tar cvzf simulador.tar.gz *.c *.h Makefile

