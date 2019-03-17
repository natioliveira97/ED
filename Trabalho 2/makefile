OBJ = Interface.o Cruzamentos.o Lista.o
BIN = trabalho

all: ${OBJ} Menu.c
	g++ -o ${BIN} Menu.c ${OBJ} -L. -l personagem -l playAPC -I.

Interface.o: Interface.h Interface.c
	g++ -c Interface.c

Cruzamentos.o: Cruzamentos.h Cruzamentos.c
	g++ -c Cruzamentos.c

Lista.o: Lista.h Lista.c
	g++ -c Lista.c


clean: ${OBJ} 
	rm -rf ${OBJ} ${BIN}
