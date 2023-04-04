all: item.o graph.o main.o path.o
	gcc -g item.o graph.o path.o main.o -o exec -std=c99 -Wall; make clean

item.o:
	gcc -g -c item.c -o item.o

path.o:
	gcc -g -c path.c -o path.o

graph.o:
	gcc -g -c graph.c -o graph.o

main.o:
	gcc -g -c main.c -o main.o

clean:
	rm *.o

run:
	(echo ../TestCases/1.in) | valgrind ./exec