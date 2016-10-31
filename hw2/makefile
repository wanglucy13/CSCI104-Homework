CC = g++
CPPFLAGS = -g -Wall

all: stackdbl.o llistdbl.o alistint.o test test2 postfix

llistdbl.o: llistdbl.cpp llistdbl.h
	$(CC) $(CPPFLAGS) llistdbl.cpp -o llistdbl.o -c

test: test.cpp llistdbl.o
	$(CC) $(CPPFLAGS) test.cpp llistdbl.o -o test

alistint.o: alistint.cpp alistint.h
	$(CC) $(CFLAGS) alistint.cpp -o alistint.o -c

test2: test2.cpp alistint.o
	$(CC) $(CFLAGS) test2.cpp alistint.o -o test2

stackdbl.o: stackdbl.cpp stackdbl.h
	$(CC) $(CFLAGS) stackdbl.cpp -o stackdbl.o -c

postfix: postfix.cpp stackdbl.o llistdbl.o
	$(CC) $(CFLAGS) postfix.cpp stackdbl.o llistdbl.o -o postfix

clean: 
	rm -f test *.o
	rm -f test2 *.o
	rm -f postfix *.o
