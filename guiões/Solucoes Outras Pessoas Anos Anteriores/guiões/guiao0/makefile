CFLAGS=-g
simple: mainSor.o simpleSor.o
	gcc $(CFLAGS) -o simple mainSor.o simpleSor.o

mainSor.o: mainSor.c simpleSor.h

simpleSor.o: simpleSor.c simpleSor.h

clean:
	rm *.o simple