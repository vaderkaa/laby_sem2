#pragma once

#include "Drone.hpp"

class DroneFleet
{
private:
    Drone** fleet;
    int capacity;
    int size;

public:
    DroneFleet(int initial_capacity = 100);
    ~DroneFleet();

    void add_drone(const std::string& model, int battery = 100); //wartosci domyslne mozna dawac nie tylko w konstruktorach
    void print_fleet() const;

    DroneFleet(const DroneFleet& other);
    DroneFleet& operator=(const DroneFleet& other);
    DroneFleet(DroneFleet&& other);
    DroneFleet& operator=(DroneFleet&& other);
};