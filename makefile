CC=gcc
CFLAGS=-I.
DEPS = cards.h stdbool.h
OBJ = cards.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cards: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	
clean:
	rm -rf *.o