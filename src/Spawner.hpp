#pragma once

#include "Vector.hpp"
#include "Integrator.hpp"

/// Class responsible for creating new particles in the world.
class Spawner {
public:
    /// Constructs a spawner to spawn particles in given integrator.
    Spawner(Integrator& integrator) : _integrator(integrator) {}

    /// Spawn a particle according to user choices.
    void spawn_particle();

    /// Prompt a ImGui UI to let user choose the particle properties.
    void ask_ui();

    /// Check if a particle should spawn now.
    void update(double current_time);

private:
    Integrator& _integrator;     ///< Integrator to spawn particles in.
    double _next_time = 0;       ///< When to spawn next particle.
    bool   _autofire = true;     ///< Should particles be spawned without user action.
    float  _delay_s = 0.3;       ///< Delay between consecutive particles.
    int    _type = 0;            ///< Type of the particle to be spawned.
    float   _mass = 10;          ///< Mass of the particle to be spawned.
    float   _damp = 1;           ///< Damping of the particle to be spawned.
    Vector3 _velocity = {0,0,0}; ///< Velocity of the particle to be spawned.
};