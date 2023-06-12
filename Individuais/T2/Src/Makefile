FILES_O = main.o graph.o item.o
CC = g++
C_FLAGS = -g -Wall -std=c++11

all: $(FILES_O)
	${CC} $(FILES_O) ${C_FLAGS} -o exec; make clean;

main.o:
	${CC} ${C_FLAGS} -c main.cpp -o main.o

graph.o:
	${CC} ${C_FLAGS} -c pkg/graph/Graph.cpp -o graph.o

item.o:
	${CC} ${C_FLAGS} -c pkg/item/Item.cpp -o item.o

clean:
	rm *.o

run:
	valgrind ./exec 