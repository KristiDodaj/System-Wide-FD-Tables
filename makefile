CC = gcc
CFLAGS = −Wall −g −std=c99 −Werror

all: fdTables

fdTables: DataCollection.o Output.o
	$(CC) $(CFLAGS) −o $@ $^

.%o: %.c datacollection.h
	$(CC) $(CFLAGS) −c $<

.PHONY: clean
clean:
	rm ∗.o