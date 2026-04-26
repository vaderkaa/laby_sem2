#include "Drone.hpp"
#include "DroneFleet.hpp"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int main() {
    std::cout << "--- ETAP 1: Inteligenty wskaznik ---" << std::endl;
    {
        // TODO: Utworz inteligentny wskaznik typu std::unique_ptr zarzadzajacy nowym obiektem klasy Drone
        // Model: "Mavic", Bateria: 90
        std::unique_ptr<Drone> d1 = std::make_unique<Drone>("Mavic", 90);
        
        // TODO: Wywolaj metode print() uzywajac stworzonego wskaznika
        d1->print();
        
        std::cout << "Liczba dronow (powinno byc 1): " << Drone::get_active_count() << std::endl;
    } 
    // Tutaj wskaznik wyjdzie poza zakres - sprawdz w konsoli, czy destruktor sie wywolal!
    std::cout << "Liczba dronow po bloku (powinno byc 0): " << Drone::get_active_count() << std::endl;

    std::cout << "\n--- ETAP 2: Dynamiczna tablica i fleet ---" << std::endl;
    DroneFleet fleet(3);
    fleet.add_drone("Biedronka", 100);
    fleet.add_drone("Phantom", 50);
    fleet.print_fleet();

    std::cout << "\n--- ETAP 3: Regula 5 (Kopiowanie i Przenoszenie) ---" << std::endl;
    
    std::cout << "Test konstruktora kopiujacego:" << std::endl;
    {
        DroneFleet fleetCopy = fleet; //wywoluje konstruktor kopiujacy
        fleetCopy.add_drone("SpyDrone", 10);
        fleetCopy.print_fleet();
    }
    //fleetCopy umarl

    std::cout << "\nTest semantyki przenoszenia (Move):" << std::endl;
    
    // TODO: Stworz nową flote 'movedFleet' i uzyj std::move
    // aby przeniesc do niej zawartosc obiektu 'fleet' (uzyj konstruktora przenoszacego)
    DroneFleet movedFleet = std::move(fleet); //MOVE ZAMIENIA L WARTOSC NA R WARTOSC, ZEBY DALO SIE UZYC KOSTRUKTORA PRZENOSZACEGO!!!
    //f2 = std::move(f1) tez zadziala na cos juz istniejacego
    
    std::cout << "Flota po przeniesieniu (movedFleet):" << std::endl;
    // TODO: Wywolaj print_fleet() na movedFleet
    movedFleet.print_fleet();
    
    std::cout << "Oryginalna flota po przeniesieniu (powinna byc pusta):" << std::endl;
    fleet.print_fleet();


    std::cout << "\n--- ETAP 4 (Bonus): shared_ptr ---" << std::endl;
{
    // Tworzymy shared_ptr do drona (używamy make_shared dla wydajności)
    std::shared_ptr<Drone> dronePtr = std::make_shared<Drone>("SharedMavic", 100);
    std::cout << "Licznik uzytkownikow (po stworzeniu): " << dronePtr.use_count() << std::endl;

    {
        // Kopiujemy go do drugiego shared_ptr
        std::shared_ptr<Drone> anotherPtr = dronePtr; 
        std::cout << "Licznik uzytkownikow (po skopiowaniu): " << dronePtr.use_count() << std::endl; //use.count() jest do testow
        
        anotherPtr->print();
        std::cout << "Zaraz zginie 'anotherPtr'..." << std::endl;
    } 
    //anotherPtr przestaje istniec, ale dron NIE zostaje usuniety (ma licznik 1 dalej)

    std::cout << "Licznik uzytkownikow (po wyjsciu z bloku): " << dronePtr.use_count() << std::endl;

    std::unique_ptr<Drone> p1 = std::make_unique<Drone>("Mavic");
    //std::unique_ptr<Drone> p2 = p1 blad nie mozna tak kopiowac

    std::unique_ptr<Drone> p2 = std::move(p1); //JAK PRZENIESC UNIQUE_PTR!!!
    //p2 ma drona, a p1 jest pusty (nullptr)

    std::cout << "Zaraz zginie 'dronePtr'..." << std::endl;

    return 0;
}
}