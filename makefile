CC = gcc
CFLAGS = -Wall -std=c99
OBJ = Output.o DataCollection.o 

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

.PHONY: clean
clean:
	rm *.o