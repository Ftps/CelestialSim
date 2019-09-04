#ifndef CELEST
#define CELEST

#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>



class Body {
    long double mass, pos[3];
}




#endif
