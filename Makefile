CC = g++
CFLAGS = -std=c++14 -c 
OBJDIR = Objects
all: prog

debug: CFLAGS += -g
debug: prog


prog: main.o DBNode.o DBGraph.o
	$(CC) $(OBJDIR)/main.o  $(OBJDIR)/DBNode.o  $(OBJDIR)/DBGraph.o -o prog

main.o: main.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)/$@

DBNode.o: DBNode.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) DBNode.cpp -o $(OBJDIR)/$@

DBGraph.o: DBGraph.cpp 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) DBGraph.cpp -o $(OBJDIR)/$@


clean:
	rm -rf *.o
		rm -rf $(OBJDIR)/*.o


