#include <iostream>

#include "bounded_buffer.hpp"

int buffer_size(const bounded_buffer* buffer)
{
    return buffer->buffer.size();
}

int buffer_capacity(const bounded_buffer* buffer)
{
    return buffer->capacity;
}

void flush_buffer(bounded_buffer* buffer)
{
    for(int i = 0; i < buffer->buffer.size(); i++)
    {
        std::cout << buffer->buffer[i] << std::endl;
    }
    std::cout << "=====" << std::endl;
    buffer->buffer.clear();
}

void add_to_buffer(bounded_buffer* buffer, std::string line)
{
    if(buffer->buffer.size() == buffer->capacity)
    {
        std::cout << "Przekroczono limit rozmiaru bufora." << std::endl;
        return;
    }
    buffer->buffer.push_back(line);
}