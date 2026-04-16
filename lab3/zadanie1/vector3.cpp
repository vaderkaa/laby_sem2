#include "vector3.hpp"

#include <cmath>
#include <iostream>

namespace l2
{

void vector3_init(Vector3& vec) //referencja
{
    vec.v[0]=0;
    vec.v[1]=0;
    vec.v[2]=0;
}

void vector3_init(Vector3& vec, double x, double y, double z)
{
    vec.v[0]=x;
    vec.v[1]=y;
    vec.v[2]=z;
}

double vector3_length(const Vector3& vec)
{
    double result=0.0;
    for(int i=0; i<3; i++)
        result+=vec.v[i]*vec.v[i];
    result=sqrt(result);
    return result;
}

void vector3_mul(Vector3& vec, double a)
{
    for(int i=0; i<Vector3::VECTOR_SIZE; i++) //dwukropek uzywany do dobrania sie do czegos, co nalezy do calego typu (klasy, struktury)
        vec.v[i]=vec.v[i]*a; //VECTOR_SIZE jest static, rozmiar wektora jest wspolny dla wszystkich Vector3
}

double vector3_x(const Vector3& vec)
{
    return vec.v[0];
}

double vector3_y(const Vector3& vec)
{
    return vec.v[1];
}

double vector3_z(const Vector3& vec)
{
    return vec.v[2];
}

Vector3 vector3_add(const Vector3& vec1, const Vector3& vec2)
{
    Vector3 result;
    for(int i=0; i<3; i++)
    {
        result.v[i]=vec1.v[i]+vec2.v[i];
    }
    return result;
}

void vector3_print(const Vector3& vec)
{
    std::cout<<"["<<vector3_x(vec)<<","<<vector3_y(vec)<<","<<vector3_z(vec)<<"]"<<std::endl;
}

}   // namespace l2
