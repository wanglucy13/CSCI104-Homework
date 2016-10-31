## README

This folder contains the provided code for hw2. 

- **Name**: Yi Wang
- **USC ID**: 1114413388
- **Email**: wang796@usc.edu

Makefile is included for test files as well as postfix.cpp

Questions 1 and 6 are in hw2.txt file

llistdbl.cpp:
	compile: make test
	run: ./test

alistint.cpp:
	compile: make test2
	run: ./test2

stackdbl.cpp/postfix.cpp:
	compile: make postfix
	run: ./postfix "inputfile".in "outputfile".out
	Must have input and output file to run postfix
	stackdbl is implemented in postfix