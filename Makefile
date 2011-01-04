
all: lecc

parser/parser.o:
	cd parser/; \
	make all

ast/ast.o:
	cd ast/; \
	make all


clean:
	cd parser/; \
	make clean
	cd ast/; \
	make clean
	rm -f *.o lecc

lecc: main.cpp parser/parser.o parser/scanner.o ast/ast.o 
	g++  -o $@ $^
	


