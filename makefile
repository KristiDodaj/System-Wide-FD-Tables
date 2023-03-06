CC = gcc
CFLAGS = -Wall -std=c99
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c datacollection.h
	$(CC) $(CFLAGS) -c $< datacollection.h

.PHONY: clean
clean:
	rm *.o