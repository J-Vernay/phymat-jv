#pragma once

#include "Vector.hpp"

class Integrator;

class Spawner {
public:
    Spawner(Integrator& integrator) : _integrator(integrator) {}

    void spawn_projectile();

    void ask_ui();

    void update(double current_time);

private:
    Integrator& _integrator;
    bool   _autofire = false;
    float  _delay_s = 0.5;
    int    _type = 0;
    double _next_time = 0;
    int    _id = 0;
    Vector3 _accel = {0,0,0};
};