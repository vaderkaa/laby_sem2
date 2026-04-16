#pragma once

struct Image
{
    int** pixels = nullptr; //wskaznik na tablice wskaznikow
    int rows;
    int columns;
};

void create_image(Image& image, int rows, int columns, int value);

void destroy_image(Image& image);

void print_image(const Image& image);

Image copy_image(const Image& image);
