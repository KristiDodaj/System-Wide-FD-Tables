CC = gcc
CFLAGS = -Wall -std=c99
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Output.o: $(OBJ)
	$(CC) $(CFLAGS) -c $< 

DataCollection.o: DataCollection.c datacollection.h
	$(CC) $(CFLAGS) -c $< 	

.PHONY: clean
clean:
	rm *.o
