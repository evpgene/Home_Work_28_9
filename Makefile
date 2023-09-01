.PHONY: all clean install uninstall

LINK = sudo g++ -std=c++20 -o
COMPILE = sudo g++ -std=c++20 -g -c -o 


all: main

main.o: main.cpp
	$(COMPILE) main.o main.cpp

main: main.o
	$(LINK) main main.o





