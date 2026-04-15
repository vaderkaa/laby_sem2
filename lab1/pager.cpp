#include <iostream>

#include "bounded_buffer.hpp"

int main()
{
    bounded_buffer buffer;
    std::string line;
    buffer.buffer.clear();
    buffer.capacity = 4;
    while(std::getline(std::cin, line))
    {
        add_to_buffer(&buffer, line);
        if(buffer_size(&buffer) == buffer_capacity(&buffer))
            flush_buffer(&buffer);
    }
    std::cout << "Limit rozmiaru: " << buffer_capacity(&buffer) << std::endl;
    std::cout << "Ilosc zgromadzonych linii w buforze: " << buffer_size(&buffer) << std::endl;
    std::cout << "Zawartosc buffora: " << std::endl;
    if(buffer_size(&buffer)==0)
        std::cout << "Bufor jest pusty." <<std::endl;
    else
        flush_buffer(&buffer);
    /*while(std::getline(std::cin, s))
    {
        //std::cout << s << std::endl;
        v.push_back(s);
        if(v.size() == 4)
        {
            for(int i = 0; i < 4; i++)
            {
                std::cout << v[i] << std::endl;
            }
            std::cout << "=====" << std::endl;
            v.clear();
        }
    }*/
    return 0;
}