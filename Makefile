CC = g++
CFLAGS = -std=c++17 -c 
OBJDIR = Objects
all: prog

debug: CFLAGS += -g
debug: prog
verbose: CFLAGS += -v
verbose: prog

OBJECTS = $(wildcard $(OBJDIR)/*.o)

prog: main.o DBGraph.o simdjson.o NodeAttribute.o PersonAttribute.o JsonAttribute.o Edge.o CipherParser.o
	$(CC)  $(OBJECTS) -o prog

main.o: main.cpp 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) main.cpp -o $(OBJDIR)/$@

DBGraph.o: DBGraph.cpp  DBGraph.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) DBGraph.cpp -o $(OBJDIR)/$@
simdjson.o: simdjson.cpp simdjson.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) simdjson.cpp -o $(OBJDIR)/$@

NodeAttribute.o: NodeAttribute.cpp NodeAttribute.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) NodeAttribute.cpp -o $(OBJDIR)/$@

PersonAttribute.o: PersonAttribute.cpp PersonAttribute.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) PersonAttribute.cpp -o $(OBJDIR)/$@

JsonAttribute.o: JsonAttribute.cpp JsonAttribute.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) JsonAttribute.cpp -o $(OBJDIR)/$@

Edge.o: Edge.cpp Edge.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) Edge.cpp -o $(OBJDIR)/$@

CipherParser.o: CipherParser.cpp CipherParser.h 
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) CipherParser.cpp -o $(OBJDIR)/$@
clean:
		rm -rf *.o
		rm -rf $(OBJDIR)/*.o


