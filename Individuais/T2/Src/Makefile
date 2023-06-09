FILES_O = main.o graph.o path.o item.o

all: $(FILES_O)
	gcc -g $(FILES_O) -std=c99 -Wall -o exec; make clean;

main.o:
	gcc -g -c main.c -o main.o

graph.o:
	gcc -g -c pkg/graph/graph.c -o graph.o

path.o:
	gcc -g -c pkg/path/path.c -o path.o

item.o:
	gcc -g -c pkg/item/item.c -o item.o

clean:
	rm *.o

run:
	valgrind ./exec < ../TestCases/in/4.in