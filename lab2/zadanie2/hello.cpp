#include "hello.hpp"

#include <iostream>

static int HELLO_COUNT = 0;

namespace hello
{
    void print(std::string name)
    {
        HELLO_COUNT++;
        std::cout << HELLO_COUNT << ". Hello " << name << "." << std::endl;
    }
}