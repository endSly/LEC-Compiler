CC = g++
CFLAGS = -Os -I"."

all: lecc


ast/ast.o:
	cd ast/; \
	make all


parser/parser.o:
	cd parser/; \
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

lecc: main.cpp ast/ast.o parser/parser.o parser/scanner.o execengine/execengine.o execengine/kernelobjs.o 
	$(CC) $(CFLAGS) -o $@ $^
	


