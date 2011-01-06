CC = g++
CFLAGS = -c -I".." -Os

clean:
	rm -f *.o

execengine.o: ExecEngine.cpp
	$(CC) $(CFLAGS) -o $@ $^
	
kernelobjs.o: KernelObjects.cpp
	$(CC) $(CFLAGS) -o $@ $^

all: execengine.o kernelobjs.o