CC = gcc
CFLAGS = -Wall
OBJ = Output.o DataCollection.o datacollection.h

all: fdTables

fdTables: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

.PHONY: clean
clean:
	rm *.o

.PHONY2: cleanText
cleanText:
	rm compositeTable.txt

.PHONY3: cleanBinary
cleanBinary:
	rm compositeTable.bin