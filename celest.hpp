#ifndef CELEST
#define CELEST

#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

#include <GL/glew.h>

#include "Vector3.hpp"

#define LOG {std::cout << " IN FILE " << __FILE__ << " IN LINE " << __LINE__ << std::endl; fflush(stdout);}

#define CONFIG_FILE "Config/val.conf"
#define ULI unsigned long int

struct Body {
    long double mass, r;
    std::vector<Vector3> pos, vel;
};

struct Ship {
    long double delta_v;
    std::vector<Vector3> pos, vel;

    void change_speed(Vector3);
};

struct Definition {
    long double G, dt;
    ULI ahead;
};

class Simulator {
public:
    std::vector<Body> bod;
    std::vector<Ship> ship;
    Definition d;
    long double t;

    std::vector<Vector3> k1, k2, k3, k4;
    Vector3 r_ij, aux;

    void init_sim();
    void runge_kutta_bod();
    void runge_kutta_ship();


    Simulator();
    Simulator(Definition de);
    void add_body(Body);
    void add_ship(Ship);
    void main_cycle();
};


#endif
