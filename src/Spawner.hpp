#pragma once

#include "Vector.hpp"
#include "Integrator.hpp"

// This class is responsible for creating new particles in the world.
class Spawner {
public:
    Spawner(Integrator& integrator) : _integrator(integrator) {}

    // Spawn a particle according to user choices.
    void spawn_particle();

    // Prompt a ImGui UI to let user choose the particle properties.
    void ask_ui();

    // Check if a particle should spawn now.
    void update(double current_time);

private:
    Integrator& _integrator;
    double _next_time = 0;
    // v  User choices storage
    bool   _autofire = true;
    float  _delay_s = 0.3;
    int    _type = 0;
    float   _mass = 10;
    float   _damp = 1;
    Vector3 _velocity = {0,0,0};
};