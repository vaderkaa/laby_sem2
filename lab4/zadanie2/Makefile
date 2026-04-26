CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l3

l3: main.o Subtask.o Task.o
	${CXX} ${LDFLAGS} main.o Subtask.o Task.o -o l3

main.o: main.cpp Subtask.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

Subtask.o: Subtask.cpp Subtask.hpp
	${CXX} ${CXXFLAGS} -c Subtask.cpp -o Subtask.o

Task.o: Task.cpp Subtask.hpp Task.hpp
	${CXX} ${CXXFLAGS} -c Task.cpp -o Task.o

clean:
	rm -f *.o l3