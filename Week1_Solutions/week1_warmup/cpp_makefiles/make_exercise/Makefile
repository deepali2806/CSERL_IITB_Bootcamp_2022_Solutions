CC=g++
CFLAGS=-I .
DEPS = functions.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: factorial.o hello.o 
	$(CC) -o $@ $^ $(CFLAGS) main.cpp

clean: 
	rm a.out
