CC = g++
CFLAGS = -Os -I"."

all: lecc

parser/parser.o:
	cd parser/; \
	make all

ast/ast.o:
	cd ast/; \
	make all

execengine/execengine.o:
	cd execengine/; \
	make all


clean:
	cd parser/; \
	make clean

	cd ast/; \
	make clean

	cd execengine/; \
	make clean

	rm -f *.o lecc

lecc: main.cpp ast/AST.o parser/parser.o parser/scanner.o execengine/execengine.o execengine/kernelobjs.o 
	$(CC) $(CFLAGS)  -o $@ $^
	


