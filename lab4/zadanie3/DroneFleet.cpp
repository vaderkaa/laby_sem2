#include "Drone.hpp"
#include "DroneFleet.hpp"

#include <iostream>

DroneFleet::DroneFleet(int initial_capacity) : capacity(initial_capacity), size(0)
{
    this->fleet = new Drone*[capacity]; //tworzymy miejsce w pamieci na wskazniki na drony
    //playlista tworzyla miejsce w pamieci dla piosenek i od razu je tworzyla, bo byl od tego konstruktor bezargumentowy
    for (int i = 0; i < capacity; ++i) 
    {
        this->fleet[i] = nullptr; //musimy ustawic kazde miejsce na drona na nullptr!!!
    }
}

DroneFleet::~DroneFleet()
{
    for(int i = 0; i < size; i++)
        delete fleet[i]; //usuwam kazdego drona
    delete[] fleet; //usuwam cala liste dronow
}

void DroneFleet::add_drone(const std::string& model, int battery)
{
    if(size < capacity)
    {
        Drone* new_drone = new Drone(model, battery);
        this->fleet[size++] = new_drone;
    }
    else
    {
        std::cout << "Flota dronow jest juz pelna" << std::endl;
    }
}

void DroneFleet::print_fleet() const
{
    for(int i = 0; i < size; i++)
    {
        std::cout << i + 1 << ". ";
        fleet[i]->print();
    }
}

DroneFleet::DroneFleet(const DroneFleet& other) : capacity(other.capacity), size(other.size) 
{
    this->fleet = new Drone*[capacity]; //tworzymy nowa flote
    for (int i = 0; i < size; i++)
        this->fleet[i] = new Drone(*other.fleet[i]); //kopiujemy drony po kolei, kopiujemy zawartosc, dzieki czemu to jest GLEBOKA KOPIA
    for(int i = size; i < capacity; i++)
        this->fleet[i] = nullptr; //puste miejsca ustawiamy na nullptr
}

DroneFleet& DroneFleet::operator=(const DroneFleet& other)
{
    if(this != &other)
    {
        for (int i = 0; i < size; i++) //najpierw sprzatamy
            delete fleet[i];
        delete[] fleet;

        capacity = other.capacity;
        size = other.size;
        this->fleet = new Drone*[capacity];
        for (int i = 0; i < size; i++)
            this->fleet[i] = new Drone(*other.fleet[i]);
        for(int i = size; i < capacity; i++)
            this->fleet[i] = nullptr;
    }
    return *this;
}

DroneFleet::DroneFleet(DroneFleet&& other) : fleet(other.fleet), capacity(other.capacity), size(other.size) 
{
    other.fleet = nullptr; //kradniemy, wiec pozbywamy sie tego
    other.size = 0;
    other.capacity = 0;
}

DroneFleet& DroneFleet::operator=(DroneFleet&& other)
{
    if(this != &other)
    {
        for (int i = 0; i < size; i++) //usuwamy sobie stare
            delete fleet[i];
        delete[] fleet;

        fleet = other.fleet;
        size = other.size;
        capacity = other.capacity;

        other.fleet = nullptr; //kradniemy
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}