CC = g++
CPPFLAGS = -g -Wall

all: llistint.o copytest setint.o settest pgindex

llistint.o: llistint.cpp llistint.h
	$(CC) $(CFLAGS) -c llistint.cpp -o llistint.o

copytest: copytest.cpp llistint.o
	$(CC) $(CPPFLAGS) copytest.cpp llistint.o -o copytest

setint.o: setint.cpp setint.h 
	$(CC) $(CFLAGS) -c setint.cpp -o setint.o

settest: settest.cpp setint.o llistint.o 
	$(CC) $(CFLAGS) settest.cpp setint.o llistint.o -o settest

pgindex: pgindex.cpp setint.o llistint.o
	$(CC) $(CPPFLAGS) pgindex.cpp setint.o llistint.o -o pgindex

clean:
	rm -f copytest *.o
	rm -f setint.o
	rm -f settest *.o
	rm -f pgindex *.o