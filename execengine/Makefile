
CC = g++
CFLAGS = -c -I".." -Os

clean:
	rm -f *.o

kernelobjs.o: KernelObjects.cpp
	$(CC) $(CFLAGS) -o $@ $^

all: kernelobjs.o
	