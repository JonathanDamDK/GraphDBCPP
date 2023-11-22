CC = g++
CFLAGS = -std=c++14 -c 
all: prog

debug: CFLAGS += -g
debug: prog


prog: main.o DBNode.o DBGraph.o
	$(CC) main.o DBNode.o DBGraph.o -o prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

DBNode.o: DBNode.cpp
	$(CC) $(CFLAGS) DBNode.cpp

DBGraph.o: DBGraph.cpp 
	$(CC) $(CFLAGS) DBGraph.cpp

clean:
	rm -rf *.o

