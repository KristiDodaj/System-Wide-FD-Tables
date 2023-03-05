CC = gcc
CFLAGS = -Wall 
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c datacollection.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o