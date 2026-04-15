COMPILER=g++

.PHONY: all clean

all: main_program test

# main_program
main_program: main_program.o libhello.so
	${COMPILER} main_program.o hello.o -L. -lhello -o main_program

main_program.o: main_program.cpp hello.hpp
	${COMPILER} -c main_program.cpp -o main_program.o

# test
test: test.o liboperations.a
	${COMPILER} test.o -L. -loperations -o test

test.o: test.cpp vectors.hpp strings.hpp
	${COMPILER} -c test.cpp -o test.o

# shared library
hello.o: hello.cpp hello.hpp
	${COMPILER} -c -fPIC hello.cpp -o hello.o

libhello.so: hello.o
	${COMPILER} -shared hello.o -o libhello.so

# static library
vectors.o: vectors.cpp vectors.hpp
	${COMPILER} -c vectors.cpp -o vectors.o

strings.o: strings.cpp strings.hpp
	${COMPILER} -c strings.cpp -o strings.o

liboperations.a: vectors.o strings.o
	ar rcs liboperations.a vectors.o strings.o

clean:
	rm -rf main_program main_program.o
	rm -rf hello.o libhello.so
	rm -rf test test.o
	rm -rf vectors.o strings.o liboperations.a

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.