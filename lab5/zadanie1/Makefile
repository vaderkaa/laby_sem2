CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l5

l5: main.o
	${CXX} ${LDFLAGS} main.o -o l5

main.o: main.cpp Movie.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

clean:
	rm -f *.o l5