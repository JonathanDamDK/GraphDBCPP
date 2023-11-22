CC = g++
CFLAGS = -std=c++14 -c 
OBJDIR = Objects
all: prog

debug: CFLAGS += -g
debug: prog


prog: main.o DBNode.o DBGraph.o simdjson.o
	$(CC) $(OBJDIR)/main.o  $(OBJDIR)/DBNode.o  $(OBJDIR)/DBGraph.o $(OBJDIR)/simdjson.o -o prog

main.o: main.cpp 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)/$@

DBNode.o: DBNode.cpp DBNode.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) DBNode.cpp -o $(OBJDIR)/$@

DBGraph.o: DBGraph.cpp  DBGraph.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) DBGraph.cpp -o $(OBJDIR)/$@
simdjson.o: simdjson.cpp simdjson.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) simdjson.cpp -o $(OBJDIR)/$@

clean:
		rm -rf *.o
		rm -rf $(OBJDIR)/*.o


