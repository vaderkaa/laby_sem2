CXX=g++

.PHONY: all clean

all: pager

pager: pager.cpp bounded_buffer.cpp bounded_buffer.hpp
	${CXX} pager.cpp bounded_buffer.cpp -o pager

clean:
	rm -f pager