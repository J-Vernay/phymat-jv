#pragma once

#include <vector>
#include <math.h>

#include "Vector.hpp"
#include "Particle.hpp"
#include "Phase2/GravityGenerator.hpp"
#include "Phase2/ParticleForceGenerator.hpp"
#include "Phase2/ParticleContact.hpp"

#include "ExceptionsForWorld.hpp"

using namespace std;

#include <unordered_set>

/// Class responsible for managing game physics.
/// Has references to every particle and force of the system.
/// Contact detection is left to the user.
class World {
private:
    /// Static gravity applied for all objects whose mass is finite.
    Vector3 gravity;
    /// Time between each frame, in second.
    double deltaTime;
public:

    /// List of all particles managed by the Integrator.
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<Particle*> particleList;
    /// List of all force generators managed by the Integrator.
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<ParticleForceGenerator*> registerOfForces;

    /// Constructs an empty Integrator (with no particles and no force generators).
    World();

    /// Get the current gravity.
    Vector3 getGravity() const { return gravity; }
    /// Get the current framerate.
    double getFrameRate() const { return 1/deltaTime; }

    /// Set the world gravity.
    void setGravity(Vector3 g);
    /// Set the framerate (number of frames = steps per second).
    void setFrameRate(double);

    /// Main function to apply all forces to all particles
    /// and move them according to them.
    /// Clean all particle force accumulators after integration.
    /// You may add custom force to particles accumulators between
    /// two invocations of this function.
    /// No collisions detection is done at this point.
    void integrate();

    /// Resolve given contacts between particles.
    /// You are responsible to detect collisions between particles.
    void resolveContacts(std::vector<ParticleContact>  contacts);

    /// Output textual representation of Integrator.
    friend ostream& operator<<(ostream& os, const World&);
};
