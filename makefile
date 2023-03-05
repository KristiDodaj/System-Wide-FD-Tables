CC = gcc
CFLAGS = -Wall 
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Output.o: Output.c 
	$(CC) $(CFLAGS) -c Output.c datacollection.h

DataCollection.o: DataCollection.c datacollection.h
	$(CC) $(CFLAGS) -c DataCollection.c

.PHONY: clean
clean:
	rm *.o