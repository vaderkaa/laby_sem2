#include "vector3.hpp"

#include <iostream>
#include <vector>

using namespace l2;

/*void print_readable_character(std::byte byte)
{
    if (byte >= std::byte{0x20} && byte <= std::byte{0x7E})
        std::cout << static_cast<char>(byte);
    else
        std::cout << ".";  // Non readable character cannot be shown in the console
}

void dump_memory(std::byte* start, size_t count)
{
    const long int window_width = 8;

    // STAGE 3: Implement me!
    // Hint: you can use print_readable_character function to print arbitrary byte as character
}*/

int main()
{
    std::cout << "STAGE 1" << std::endl;

    Vector3 v1 = BaseVector1;
    Vector3 v2 = BaseVector2;
    Vector3 v3 = BaseVector3;

    vector3_mul(v1, 3);
    vector3_mul(v2, 5);
    vector3_mul(v3, 7);

    Vector3 result_vector = vector3_add(v1, vector3_add(v2, v3));
    vector3_print(result_vector);
    //--------------------------------------------------
    std::cout << "STAGE 2 and 3" << std::endl;

    const int array_size = 10;

    //STOS
    std::cout<< "--- STOS ---" << std::endl;

    Vector3 stack_array[array_size];

    for(int i=0; i<array_size; i++)
    {
        vector3_init(stack_array[i], static_cast<double>(i), static_cast<double>(i), static_cast<double>(i)); //zmienia int na double
        std::cout << std::hex << &stack_array[0] << std::endl; //czy cala tablica nie zmienia miejsca w pamieci
    }

    for(size_t i=0; i<array_size; i++)
        std::cout << vector3_length(stack_array[i]) << std::endl;

    //STERTA - recznie zarzadza pamiecia
    std::cout<< "--- STERTA ---" << std::endl;

    Vector3* heap_array = new Vector3[array_size]; //10 pudelek typu Vector3, zapamietuje adres pierwszego z nich

    for(int i=0; i<array_size; i++)
    {
        vector3_init(heap_array[i], static_cast<double>(i), static_cast<double>(i), static_cast<double>(i));
        std::cout << std::hex << &heap_array[0] << std::endl; //adres w pamieci pierwszego elementu rowniez nie bedzie sie zmieniac
    }

    for(size_t i=0; i<array_size; i++)
        std::cout << vector3_length(heap_array[i]) << std::endl;

    delete[] heap_array; //trzeba usunac!!!
    //[] bo uzywalam new[]

    // std::vector - wewnetrznie zarzadza pamiecia
    std::cout<< "--- STD::VECTOR ---" << std::endl;

    std::vector<Vector3> vector_of_vectors3;

    for(int i=0; i<array_size; i++)
    {
        Vector3 temp;
        vector3_init(temp, static_cast<double>(i), static_cast<double>(i), static_cast<double>(i));
        vector_of_vectors3.push_back(temp);
        std::cout << std::hex << &vector_of_vectors3[0] << std::endl;
    }

    for(size_t i=0; i<vector_of_vectors3.size(); i++)
        std::cout << vector3_length(vector_of_vectors3[i]) << std::endl; //adresy moga sie zmieniac, bo wszystkie elementy wektora musza byc jeden za drugim w pamieci
    //jesli Vector3* moj_ukochany_wektor = &vector_of_vectors[2]; to po push_back adres moglby sie zmienic, a moj_ukochany_wektor wskazywalby na pustke
    //--------------------------------------------------
    std::cout << "STAGE 4" << std::endl;

    //--------------------------------------------------
    std::cout << "STAGE 5" << std::endl;

    return 0;
}
