$OBJS = parser.o     \
	ast.o        \
	codegen.o    \

all: lecc

parser.o:
	cd parser
	make all

ast.o:


codegen.o:


lecc: $(OBJS)


