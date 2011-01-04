
CC = g++
CFLAGS = -c -I".." -Os

clean:
	rm -f parser.hpp parser.cpp  scanner.cpp *.o

parser.cpp: parser.y
	bison -d -o $@ $^
	
parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	lex -o $@ $^


parser.o: parser.cpp 
	$(CC) $(CFLAGS) -o $@ $^

scanner.o: scanner.cpp
	$(CC) $(CFLAGS) -o $@ $^

all: scanner.o parser.o 
	