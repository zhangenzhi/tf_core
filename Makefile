all: main

main: main.o test.o
	g++ -o main main.o test.o

test.o: test.h test.cc
	g++ -c test.cc

main.o: main.cpp
	g++ -c main.cpp