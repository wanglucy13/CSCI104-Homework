CXX=g++
CXXFLAGS=-g -Wall 

all: test rectangle

test: test.cpp rbbst.h bst.h
	$(CXX) $(CXXFLAGS) test.cpp -o test

rectangle: rectangle.cpp
	$(CXX) $(CXXFLAGS) rectangle.cpp -o rectangle


clean:
	rm -f test *.o
	rm -f rectangle *.o
