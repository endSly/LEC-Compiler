$OBJS = parser.o     \
	ast.o        \
	godegen.o    \

all: lecc

lecc: $(OBJS)
