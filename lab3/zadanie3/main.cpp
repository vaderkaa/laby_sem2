#include "images.hpp"
#include <iostream>

int main()
{
    Image image;
    create_image(image, 3, 5, 7);
    if(image.pixels != nullptr)
        image.pixels[1][2] = 1;
    std::cout << "Zdjecie:" << std::endl;
    print_image(image);

    Image copied_image = copy_image(image);
     if(copied_image.pixels != nullptr)
        copied_image.pixels[1][2] = 9;
    std::cout << "Skopiowane zdjecie:" << std::endl;
    print_image(copied_image);

    destroy_image(image);
    destroy_image(copied_image);
    if(image.pixels == nullptr && copied_image.pixels == nullptr)
        std::cout << "Pamiec zostala pomyslnie zwolniona." << std::endl;

    return 0;
}
