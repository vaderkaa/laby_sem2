#include "images.hpp"
#include <iostream>

void create_image(Image& image, int rows, int columns, int value)
{
    image.rows = rows;
    image.columns = columns;
    image.pixels = new int*[rows];
    for(int i = 0; i < rows; i++)
    {
        image.pixels[i] = new int[columns];
        for(int j = 0; j < columns; j++)
            image.pixels[i][j] = value;

    }
}

void destroy_image(Image& image)
{
    if(image.pixels == nullptr)
        return;

    for(int i = 0; i < image.rows; i++)
        delete[] image.pixels[i];

    delete[] image.pixels;

    image.pixels = nullptr;
    image.rows = 0;
    image.columns = 0;
}

void print_image(const Image& image)
{
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.columns; j++)
            std::cout << image.pixels[i][j] << " ";
        std:: cout << std::endl;
    }
}

Image copy_image(const Image& image)
{
    Image new_image;
    create_image(new_image, image.rows, image.columns, 0);

    for(int i = 0; i < image.rows; i++)
        for(int j = 0; j < image.columns; j++)
            new_image.pixels[i][j] = image.pixels[i][j];

    return new_image;
}
