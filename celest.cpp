#include "celest.hpp"

void Ship::change_speed(Vector3 v)
{
    long double ve = v.modulus();

    if(ve > delta_v){
        v.scalar_self(delta_v/ve);
    }

    //vel.add_to_self(v);
}




Simulator::Simulator()
{
    std::ifstream fp(CONFIG_FILE);

    fp >> d.G;
    fp >> d.dt;
    fp >> d.ahead;
}

Simulator::Simulator(Definition de)
{
    d = de;
}

void Simulator::init_sim()
{
    /* Put on screen saying "Preparing simulation..." */

    for(int i = 0; i < (int)bod.size(); ++i)
    {
        bod[i].pos.reserve(d.ahead);
        bod[i].vel.reserve(d.ahead);
    }

    k1.reserve(bod.size());
    k2.reserve(bod.size());
    k3.reserve(bod.size());
    k4.reserve(bod.size());

    t = 0;

    if(bod.size() != 0){
        for(ULI a = 0; a < d.ahead-1; ++a){
            runge_kutta_bod();
        }
    }

}

void Simulator::runge_kutta_bod()
{

    if(bod[0].pos.size() == bod[0].pos.capacity()){
        for(ULI i = 0; i < bod.size(); ++i){
            bod[i].pos.erase(bod[i].pos.begin());
            bod[i].vel.erase(bod[i].vel.begin());
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){
        k1[i].null();
        k2[i].null();
        k3[i].null();
        k4[i].null();
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k1 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            r_ij = bod[i].pos.back().sub_to_vec(bod[j].pos.back());
            k1[i].add_to_self(r_ij.scalar(-d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k2 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            aux = bod[i].pos.back().add_to_vec(k1[i].scalar(0.5));
            r_ij = aux.sub_to_vec(bod[j].pos.back().add_to_vec(k1[j].scalar(0.5)));
            k2[i].add_to_self(r_ij.scalar(d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k3 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            aux = bod[i].pos.back().add_to_vec(k2[i].scalar(0.5));
            r_ij = aux.sub_to_vec(bod[j].pos.back().add_to_vec(k2[j].scalar(0.5)));
            k3[i].add_to_self(r_ij.scalar(d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k4 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            aux = bod[i].pos.back().add_to_vec(k3[i]);
            r_ij = aux.sub_to_vec(bod[j].pos.back().add_to_vec(k3[j]));
            k4[i].add_to_self(r_ij.scalar(d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){
        k2[i].scalar_self(2);
        k3[i].scalar_self(2);
        aux = k1[i].add_to_vec(k2[i].add_to_vec(k3[i].add_to_vec(k4[i])));
        aux.print_coord();
        LOG
        bod[i].vel.push_back(bod[i].vel.back().add_to_vec(aux.scalar(1.0/6.0)));
        bod[i].pos.push_back(bod[i].pos.back().add_to_vec(bod[i].vel.back().scalar(d.dt)));
    }

    aux.scalar(1.0/6.0).print_coord();
    LOG
    bod[0].vel.back().print_coord();
    LOG
}

void Simulator::add_body(Body b)
{
    bod.push_back(b);
}

void Simulator::add_ship(Ship s)
{
    ship.push_back(s);
}

void Simulator::main_cycle()
{
    /*
    Menu to add bodies and ships to the simulation
    */

    init_sim();


    return;
}
