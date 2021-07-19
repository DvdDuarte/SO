CFLAGS=-g -Wall -O2 -Wextra
pessoas: main.o pessoas.o
	gcc $(CFLAGS) -o pessoas pessoas.o main.o

main.o: main.c pessoas.h

pessoas.o: pessoas.c pessoas.h

clean:
	rm *.o pessoas