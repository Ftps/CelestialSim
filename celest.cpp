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
        aux.null();
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            r_ij = bod[i].pos.back().sub_to_vec(bod[j].pos.back());
            aux.add_to_self(r_ij.scalar(d.G*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
        bod[i].vel.push_back(bod[i].vel.back().add_to_vec(aux.scalar(d.dt)));
        bod[i].pos.push_back(bod[i].pos.back().add_to_vec(bod[i].vel.back().scalar(d.dt)));
    }

    /* for(ULI i = 0; i < bod.size(); ++i){
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
            aux = bod[i].pos.back().add_to_vec(bod[i].vel.back().add_to_vec(k1[i].scalar(0.5)));
            r_ij = aux.sub_to_vec(bod[j].pos.back().add_to_vec(k1[j].scalar(0.5)));
            k2[i].add_to_self(r_ij.scalar(d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k3 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            aux = bod[i].pos.back().add_to_vec(bod[i].vel.back().add_to_vec(k2[i].scalar(0.5)));
            r_ij = aux.sub_to_vec(bod[j].pos.back().add_to_vec(k2[j].scalar(0.5)));
            k3[i].add_to_self(r_ij.scalar(d.G*d.dt*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){ // k4 for runge-kutta
        for(ULI j = 0; j < bod.size(); ++j){
            if(i == j) continue;
            aux = bod[i].pos.back().add_to_vec(bod[i].vel.back().add_to_vec(k3[i]));
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

    */
}

void Simulator::runge_kutta_ship()
{
    if(ship[0].pos.size() == ship[0].pos.capacity()){
        for(ULI i = 0; i < bod.size(); ++i){
            ship[i].pos.erase(ship[i].pos.begin());
            ship[i].vel.erase(ship[i].vel.begin());
        }
    }

    for(ULI i = 0; i < bod.size(); ++i){
        aux.null();
        for(ULI j = 0; j < bod.size(); ++j){
            r_ij = ship[i].pos.back().sub_to_vec(bod[j].pos.back());
            aux.add_to_self(r_ij.scalar(d.G*bod[j].mass/pow(r_ij.modulus(), 3)));
        }
        ship[i].vel.push_back(ship[i].vel.back().add_to_vec(aux.scalar(d.dt)));
        ship[i].pos.push_back(ship[i].pos.back().add_to_vec(ship[i].vel.back().scalar(d.dt)));
    }
}

void Simulator::preview_ship(ULI a)
{
    aux.null();
    for(ULI a = 0; a < d.ahead-1; ++a){
        for(ULI i = 0; i < bod.size(); ++i){
            r_ij = ship[a].pos.back().sub_to_vec(bod[i].pos[a]);
            aux.add_to_self(r_ij.scalar(d.G*bod[i].mass/pow(r_ij.modulus(), 3)));
        }
        ship[a].vel.push_back(ship[a].vel.back().add_to_vec(aux.scalar(d.dt)));
        ship[a].pos.push_back(ship[a].pos.back().add_to_vec(ship[a].vel.back().scalar(d.dt)));
    }
}

void Simulator::add_body(Body b)
{
    b.pos.reserve(d.ahead);
    b.vel.reserve(d.ahead);
    aux.null();

    for(ULI a; a < d.ahead-1; ++a){
        for(ULI i = 0; i < bod.size(); ++i){
            r_ij = b.pos.back().sub_to_vec(bod[i].pos[a]);
            aux.add_to_self(r_ij.scalar(d.G*bod[i].mass/pow(r_ij.modulus(), 3)));
        }
        b.vel.push_back(b.vel.back().add_to_vec(aux.scalar(d.dt)));
        b.pos.push_back(b.pos.back().add_to_vec(b.vel.back().scalar(d.dt)));
    }

    bod.push_back(b);
}

void Simulator::add_ship(Ship s)
{
    ship.push_back(s);
    preview_ship(ship.size()-1);
}

void Simulator::change_speed(Vector3 dv, ULI i)
{
    aux = ship[i].pos[0];
    ship[i].pos.clear();
    ship[i].pos.push_back(aux);
    aux = ship[i].vel[0];
    ship[i].vel.clear();
    ship[i].vel.push_back(aux.add_to_vec(dv));

    preview_ship(i);
}

void Simulator::main_cycle()
{
    /*
    Menu to add bodies and ships to the simulation
    */

    init_sim();

    do{
        /*
        Render image on screen
        */

        /*
        Proccess events
        */

        runge_kutta_bod();
        runge_kutta_ship();

    }while(true);

    return;
}
