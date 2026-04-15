CXX=g++

.PHONY: all clean run

all: program_1 program_2

run: all
	LD_LIBRARY_PATH=. ./program_1
	LD_LIBRARY_PATH=. ./program_2

# program_1
program_1: program_1.o vars.o libgreeter.a
	${CXX} program_1.o vars.o -L. -lgreeter -o program_1

program_1.o: program_1.cpp vars.hpp
	${CXX} -c program_1.cpp -o program_1.o

vars.o: vars.cpp vars.hpp
	${CXX} -c vars.cpp -o vars.o

# program_2
program_2: program_2.o libgreeter.a librome.so
	${CXX} program_2.o -L. -lgreeter -lrome -o program_2

program_2.o: program_2.cpp greeter.hpp rome.hpp
	${CXX} -c program_2.cpp -o program_2.o

# greeter static library
greeter.o: greeter.cpp greeter.hpp
	${CXX} -c greeter.cpp -o greeter.o

libgreeter.a: greeter.o
	ar rcs libgreeter.a greeter.o

#rome dynamic library
rome.o: rome.cpp rome.hpp
	${CXX} -c -fPIC rome.cpp -o rome.o

librome.so: rome.o
	${CXX} -shared rome.o -o librome.so

clean:
	rm -rf program_1 program_1.o vars.o
	rm -rf greeter.o libgreeter.a
	rm -rf program_2 program_2.o
	rm -rf rome.o librome.so

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

# LD_LIBRARY_PATH=:$LD_LIBRARY_PATH ./main_program

# cp *.cpp *.hpp Makefile