FILES_O = main.o graph.o stack.o item.o

all: $(FILES_O)
	gcc -g $(FILES_O) -std=c99 -Wall -o exec; make clean;

main.o:
	gcc -g -c main.c -o main.o

graph.o:
	gcc -g -c pkg/graph/graph.c -o graph.o

stack.o:
	gcc -g -c pkg/stack/stack.c -o stack.o

item.o:
	gcc -g -c pkg/item/item.c -o item.o

clean:
	rm *.o

run:
	valgrind ./exec