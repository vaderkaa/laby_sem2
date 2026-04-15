#ifndef BOUNDED_BUFFER_HPP
#define BOUNDED_BUFFER_HPP

#include <string>
#include <vector>

struct bounded_buffer
{
    std::vector <std::string> buffer;
    int capacity;
};

int buffer_size(const bounded_buffer* buffer);

int buffer_capacity(const bounded_buffer* buffer);

void flush_buffer(bounded_buffer* buffer);

void add_to_buffer(bounded_buffer* buffer, std::string line);

#endif