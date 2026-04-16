#include "mini_vector.hpp"
#include <iostream>
#include <cstring>

//ETAP 1
void vector_init(MiniVector& v, int capacity)
{
    v.size = 0;
    v.capacity = capacity;
    v.elements = new char[capacity];
}

void vector_init_fill(MiniVector& v, int capacity, char init_character)
{
    v.size = capacity;
    v.capacity = capacity;
    v.elements = new char[capacity];
    
    for(int i = 0; i < capacity; i++)
        v.elements[i] = init_character;
}

void vector_print(MiniVector& v)
{
    std::cout << "Vector elements: ";

    if(v.size == 0)
    {
        std::cout << "no elements in vector." << std::endl;
        return;
    }

    for(int i = 0; i < v.size; i++)
    {
        std::cout << v.elements[i];
        if(i != v.size - 1)
            std::cout << ", ";
    }
    std::cout << std::endl;
}

void vector_destroy(MiniVector& v)
{
    delete[] v.elements;
}

//ETAP 2
void vector_expand(MiniVector& v, int new_capacity)
{
    if(v.capacity > new_capacity)
    {
        std::cout << "Cannot expand vector: new capacity is lower than current." << std::endl;
        return;
    }

    if(v.capacity == new_capacity)
    {
        std::cout << "Cannot expand vector: new capacity is same as current." << std::endl;
        return;
    }

    char* temp = new char[new_capacity];
    memcpy(temp, v.elements, v.size); //memcpy(miejsce, zrodlo, ile)
    //jesli tablica int, to v.size*sizeof(int)
    //#include <algorithm> i std::copy(v.elements, v.elements + v.size, temp)
    //ewentualnie petla temp[i] = v.elements[i]
    delete[] v.elements; //usuwamy STARE miejsce!!!
    v.elements = temp;
    v.capacity = new_capacity;
}

void vector_shrink(MiniVector& v, int new_capacity)
{
    if(v.capacity < new_capacity)
    {
        std::cout << "Cannot shrink vector: new capacity is greater than current." << std::endl;
        return;
    }

    if(v.capacity == new_capacity)
    {
        std::cout << "Cannot shrink vector: new capacity is same as current." << std::endl;
        return;
    }

    if(v.size > new_capacity)
    {
        std::cout << "Cannot shrink vector: there are elements that would be lost in the process." << std::endl;
        return;
    }

    char* temp = new char[new_capacity];
    memcpy(temp, v.elements, v.size);
    delete[] v.elements;
    v.elements = temp;
    v.capacity = new_capacity;
}

//ETAP 3
void vector_add(MiniVector& v, char new_element)
{
    if(v.size == v.capacity)
        vector_expand(v, v.capacity * 2);

    v.elements[v.size] = new_element;
    v.size++;
    std::cout << "Added " << new_element << std::endl;
}

void vector_clear(MiniVector& v)
{
    vector_destroy(v);
    vector_init(v, INIT_CAPACITY);
}

//ETAP 4
void vector_remove(MiniVector& v, int x)
{
    if(x - 1 >= v.size || x <= 0)
    {
        std::cout << "The requested element index is exceeding vector size. (Vector size: " << v.size << ". Requested idx for element removal: " << x << ")" << std::endl;
        return;
    }

    for(int i = x - 1; i < v.size - 1; i++)
        v.elements[i]=v.elements[i+1];
    v.size--;

    if(v.size * 2 < v.capacity)
        vector_shrink(v, v.capacity / 2);
}

void vector_remove_occurrences(MiniVector& v, char x)
{
    int y = 0;
    for(int i = 0; i < v.size; i++)
    {
        if(v.elements[i] == x)
            y++;
        else
            v.elements[i - y] = v.elements[i];
    }
    v.size = v.size - y;
    
    if(v.size * 2 < v.capacity)
        vector_shrink(v, v.capacity / 2);
}
