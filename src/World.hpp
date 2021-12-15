#pragma once

#include <vector>
#include <math.h>

#include "Phase3/RigidBody.hpp"
#include "Vector.hpp"
#include "Particle.hpp"
#include "Phase2/GravityGenerator.hpp"
#include "Phase2/ParticleForceGenerator.hpp"
#include "Phase2/ParticleContact.hpp"
#include "Phase4/Octree.hpp"
#include "Phase4/Contact.h"
#include "Phase4/Plane.hpp"

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

    /// List of all particles managed in the World.
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<Particle*> particleList;
    /// List of all force generators managed in the World.
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<ParticleForceGenerator*> registerOfForces;
    /// List of all rigid bodies managed in the World.
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<RigidBody*> rigidbodyList;
    /// List of all contacts of rigidbodies managed in the World
    /// Public because the user has the responsibility to keep it updated with the system.
    unordered_set<Contact*> contactList;

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

    //Fill the list of contact after testing all potential collision (due to broad phase)
    void generateContacts(std::vector<PotentialCollision> potentialCollisions);

    //Measure the distance between a point and a wall, 
    //if the distance is positiv : there is no contact between the rigidBody and the plane,
    //if the distance is negativ the is a contact and the distance is the interpenetration
    float getDistanceFromTheWall(Plane * plane, Vector3 point);
};
