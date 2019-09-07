#include "Vector3.hpp"

Vector3 Vector3::sub_to_vec(Vector3 v)
{
    for(int i = 0; i < 3; ++i){
        v.coord[i] -= coord[i];
    }

    return v;
}

Vector3 Vector3::add_to_vec(Vector3 v)
{
    for(int i = 0; i < 3; ++i){
        v.coord[i] += coord[i];
    }

    return v;
}

void Vector3::add_to_self(Vector3 v)
{
    for(int i = 0; i < 3; ++i){
        coord[i] += v.coord[i];
    }
}

long double Vector3::dot_prod(Vector3 v)
{
    long double p = 0;

    for(int i = 0; i < 3; ++i){
        p += coord[i]*v.coord[i];
    }

    return p;
}

Vector3 Vector3::cross_with_vec(Vector3 v)
{
    Vector3 vec;

    for(int i = 0; i < 3; ++i){
        vec.coord[i] = pow(-1, i)*(coord[(i+1)%3]*v.coord[(i+2)%3] - coord[(i+2)%3]*v.coord[(i+1)%3]);
    }

    return vec;
}

long double Vector3::modulus()
{
    long double m = 0;

    for(int i = 0; i < 3; ++i){
        m += coord[i]*coord[i];
    }

    return sqrt(m);
}

Vector3 Vector3::scalar(long double a)
{
    Vector3 vec;

    for(int i = 0; i < 3; ++i){
        vec.coord[i] = a*coord[i];
    }

    return vec;
}

void Vector3::scalar_self(long double a)
{
    for(int i = 0; i < 3; ++i){
        coord[i] = a*coord[i];
    }
}

void Vector3::null()
{
    for(int i = 0; i < 3; ++i){
        coord[i] = 0;
    }
}

void Vector3::print_coord()
{
    for(int i = 0; i < 3; ++i){
        std::cout << " " << coord[i];
    }
}
