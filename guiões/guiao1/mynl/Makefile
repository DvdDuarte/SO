CC = gcc
CFLAGS = -O2 -Wall
OBJS = main.o readln.o
DEPS = readln.h

all: main

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: main
	./main

.PHONY: clean
clean:
	-rm -f main *.o
