
CC = g++
CFLAGS = -c -I".." -Os

clean:
	rm -f *.o

ast.o: AST.cpp
	$(CC) $(CFLAGS) -o $@ $^

kernelobjs.o : KernelObjects.cpp
	$(CC) $(CFLAGS) -o $@ $^

all: ast.o kernelobjs.o
	