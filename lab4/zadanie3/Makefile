CXX = g++
CXXFLAGS=-std=c++17 -Wall -fsanitize=address,leak -g
LDFLAGS=-fsanitize=address,leak

all: l3

l3: main.o Drone.o DroneFleet.o
	$(CXX) $(LDFLAGS) main.o Drone.o DroneFleet.o -o l3

main.o: main.cpp Drone.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Drone.o: Drone.cpp Drone.hpp
	$(CXX) $(CXXFLAGS) -c Drone.cpp -o Drone.o

DroneFleet.o: DroneFleet.cpp Drone.hpp DroneFleet.hpp
	$(CXX) $(CXXFLAGS) -c DroneFleet.cpp -o DroneFleet.o

clean:
	rm -f *.o l3

run: all
	./all