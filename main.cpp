#include "celest.hpp"

int main(int argc, char *argv[])
{
    Simulator sim;
    Body b = {10000000000, 0.1, {{-5, 0, 0}}, {{0, 0.215219526169, 0}}}, c = {50000000000, 0.2, {{1, 0, 0}}, {{0, -0.043043905, 0}}};

    LOG

    sim.add_body(b);
    sim.add_body(c);
    sim.init_sim();

    LOG

    for(int i = 0; i < sim.bod[0].pos.size(); ++i){
        std::cout << "B:";
        sim.bod[0].pos[i].print_coord();
        std::cout << "    C:";
        sim.bod[1].pos[i].print_coord();
        std::cout << std::endl;
    }

    return 0;
}
