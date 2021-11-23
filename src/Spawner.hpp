#pragma once

#include "Vector.hpp"
#include "Phase3/Star.hpp"
#include "World.hpp"
#include "Graphics.hpp"
#include <array>
#include <optional>

/// Class responsible for creating a star in the world.
class Spawner {
public:
    /// Constructs a spawner to spawn a star in given integrator.
    Spawner(World& world) : _world(world) {}

    /// Spawn a star according to user choices.
    void spawn_star();

    /// Prompt a ImGui UI to let user choose the star properties.
    void ask_ui();
    
    /// Update the spawner, eventually adding new position of center of mass, and despawn star if negative Z.
    void update(double current_time);

    /// Draw the star and the positions of center of mass.
    void draw(ParticleRenderer& particleRenderer) const;

private:
    World& _world;        ///< World to spawn star in.
    optional<Star> _star; ///< Star being shot, or NULL if star has despawned.
    vector<Vector3> _positions; ///< Positions of center of mass.

    double _next_time = 0; ///< Next time to add a position.

    float   _mass = 10;          ///< Mass of the star to be spawned.
    float   _damp = 1;           ///< Damping of the star to be spawned.
    float   _angdamp = 1;        ///< Angular damping of the star to be spawned.
    Vector3 _velocity = {0,0,0}; ///< Velocity of the star to be spawned.
};