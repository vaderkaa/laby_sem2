#include "Drone.hpp"

#include <string>
#include <iostream>

int Drone::active_drones = 0;

Drone::Drone(const std::string& model, int battery_level) : model(model), battery_level(battery_level) { Drone::active_drones++; }
Drone::~Drone() { Drone::active_drones--; print(); std::cout << "zostal zniszczony" <<std::endl; }

void Drone::print() const
{
    std::cout << "Drone: " << model << ", battery: " << battery_level << "%" << std::endl;
}

int Drone::get_active_count()
{
    return Drone::active_drones; //tu tez musi byc z dwukropkami
}