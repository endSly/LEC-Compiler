$OBJS = parser.o     \
	ast.o        \
	codegen.o    \

all: lecc

parser.o : parser/parser.y parser/scanner.l
	cd parser
	make

ast.o :
	cd ast
	make

codegen.o :
	cd codegen
	make


lecc: $(OBJS)
