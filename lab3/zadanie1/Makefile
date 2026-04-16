CXX=g++
CXXFLAGS=-Wall -fsanitize=address,leak #przy plikach .o
LDFLAGS=-fsanitize=address,leak #przy programie wykonywalnym

.PHONY: all clean

all: l2

l2: main.o vector3.o
	${CXX} ${LDFLAGS} main.o vector3.o -o l2

main.o: main.cpp vector3.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

vector3.o: vector3.cpp vector3.hpp
	${CXX} ${CXXFLAGS} -c vector3.cpp -o vector3.o

clean:
	rm -f l2
	rm -f main.o
	rm -f vector3.o
