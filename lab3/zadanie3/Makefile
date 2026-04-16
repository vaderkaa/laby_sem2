COMPILER=g++

.PHONY: all
all: program

program: main.o images.o
	${COMPILER} -g -fsanitize=address main.o images.o -o program

main.o: main.cpp
	${COMPILER} -c main.cpp -o main.o

images.o: images.cpp images.hpp
	${COMPILER} -c images.cpp -o images.o

.PHONY: clean
clean:
	rm -f program
	rm -f main.o
	rm -f images.o
