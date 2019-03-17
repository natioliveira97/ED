# -*- MakeFile -*-

calculadora: pilha.o calculadora.o main.c
	gcc main.c calculadora.o pilha.o -o calculadora -lm

pilha.o: pilha.c pilha.h
	gcc pilha.c -c

calculadora.o: calculadora.c calculadora.h pilha.h
	gcc calculadora.c -c