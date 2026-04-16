#pragma once

//ETAP 1
static int INIT_CAPACITY = 4;

struct MiniVector
{
    char* elements = nullptr;
    int capacity = INIT_CAPACITY;
    int size = 0;
};

void vector_init(MiniVector& v, int capacity);

void vector_init_fill(MiniVector& v, int capacity, char init_character);

void vector_print(MiniVector& v);

void vector_destroy(MiniVector& v);

//ETAP 2
void vector_expand(MiniVector& v, int capacity);

void vector_shrink(MiniVector& v, int new_capacity);

//ETAP 3
void vector_add(MiniVector& v, char new_element);

void vector_clear(MiniVector& v);

//ETAP 4
void vector_remove(MiniVector& v, int x);

void vector_remove_occurrences(MiniVector& v, char x);
