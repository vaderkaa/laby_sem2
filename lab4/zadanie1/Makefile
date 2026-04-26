CXX=g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

.PHONY: all clean

all: l3

l3: main.o Song.o Playlist.o
	${CXX} ${LDFLAGS} main.o Song.o Playlist.o -o l3

main.o: main.cpp SongDuration.hpp Song.hpp
	${CXX} ${CXXFLAGS} -c main.cpp -o main.o

Song.o: Song.cpp SongDuration.hpp Song.hpp
	${CXX} ${CXXFLAGS} -c Song.cpp -o Song.o

Playlist.o: Playlist.cpp Song.hpp Playlist.hpp
	${CXX} ${CXXFLAGS} -c Playlist.cpp -o Playlist.o

clean:
	rm -f *.o l3