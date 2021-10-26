#pragma once

#include "Vector.hpp"
#include "World.hpp"
#include <array>

/// Class responsible for creating new particles in the world.
class Spawner {
    /// Max particles in system. Important to ensure '_particles'
    /// never grows after constructor, which would cause reallocation
    /// and pointer invalidation.
    static constexpr int MaxParticles = 100;
public:
    /// Constructs a spawner to spawn particles in given integrator.
    Spawner(World& integrator) : _integrator(integrator) {
        _particles.reserve(MaxParticles);
    }

    /// Spawn a particle according to user choices.
    void spawn_particle();

    /// Prompt a ImGui UI to let user choose the particle properties.
    void ask_ui();

    /// Check if a particle should spawn now.
    void update(double current_time);

private:
    World& _integrator;     ///< Integrator to spawn particles in.
    vector<Particle> _particles; ///< All living particles spawned.

    double _next_time = 0;       ///< When to spawn next particle.
    bool   _autofire = false;    ///< Should particles be spawned without user action.
    float  _delay_s = 0.3;       ///< Delay between consecutive particles.
    float   _mass = 10;          ///< Mass of the particle to be spawned.
    float   _damp = 1;           ///< Damping of the particle to be spawned.
    Vector3 _velocity = {0,0,0}; ///< Velocity of the particle to be spawned.
};