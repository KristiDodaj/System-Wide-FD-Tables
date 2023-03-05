CC = gcc
CFLAGS = -Wall -g -std=c99 -Werror
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

Output.o: Output.c 
	$(CC) $(CFLAGS) -c Output.c

DataCollection.o: DataCollection.c 
	$(CC) $(CFLAGS) -c DataCollection.c

.PHONY: clean
clean:
	rm *.o