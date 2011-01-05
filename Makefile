
all: clean lecc

parser/parser.o:
	cd parser/; \
	make all

ast/ast.o:
	cd ast/; \
	make all

execengine/kernelobjs.o:
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

lecc: main.cpp parser/parser.o parser/scanner.o ast/ast.o execengine/kernelobjs.o 
	g++  -o $@ $^
	


