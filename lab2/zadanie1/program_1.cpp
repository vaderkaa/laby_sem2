#include "greeter.hpp"
#include "vars.hpp"

#include <iostream>

int main()
{
    print_vars();
    inc_vars();
    print_vars();
    std::cout << "global_extern z pliku program_1.cpp: " << global_extern << std::endl;

    std::cout << greeter::english() << std::endl;
    std::cout << greeter::polish() << std::endl;
    std::cout << greeter::greek() << std::endl;
}