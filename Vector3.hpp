#ifndef VECTOR3
#define VECTOR3

#include <iostream>
#include <cmath>

struct Vector3 {
    long double coord[3];

    struct Vector3 sub_to_vec(struct Vector3);
    struct Vector3 add_to_vec(struct Vector3);
    void add_to_self(struct Vector3);
    long double dot_prod(struct Vector3);
    struct Vector3 cross_with_vec(struct Vector3);
    long double modulus();
    struct Vector3 scalar(long double);
    void scalar_self(long double);
    void null();
    void print_coord();
};

#endif
