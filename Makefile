CC=gcc
CFLAGS=-Wall
SRC=src/
EXEC=main
CLEAN=clean

all: $(EXEC) exec

main: liste.o coureur.o readfile.o
	$(CC) $(CFLAGS) -o $@ $^

liste.o: src/liste.c
	$(CC) $(CFLAGS) -c $^

coureur.o: src/coureur.c
	$(CC) $(CFLAGS) -c $^

readfile.o: src/readfile.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o
	rm $(EXEC)

exec:
	./$(EXEC)