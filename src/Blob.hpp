#pragma once

#include "World.hpp"
#include "Phase2/SpringForceGenerator.hpp"


/// Class representing a blob which is a set of particles linked with springs
/// (mass-spring system). It consists of two layers of particles, as explained
/// and justified in https://cowboyprogramming.com/2007/01/05/blob-physics/ .
class Blob {
public:
    /// Creates a blob with the given parameters:
    /// \param world  Where particles and forces will be added.
    /// \param centerpos Position of particle at center of blob.
    /// \param radius The distance between the blob center and the outer "skin".
    /// \param slices Number of slices used to build the blob.
    ///               The blob will have `2*slices*slices+1` particles in total.
    /// \param mass   Mass of particles.
    Blob(World& world, Vector3 centerpos, float radius, int slices, float mass);

    /// Destructor, which removes particles and forces from world.
    ~Blob();

    /// Get center particle so you can apply forces or get position.
    Particle& center() { return _particles.front(); }

    vector<Particle>& particles() { return _particles; }

    void addInternalContacts(vector<ParticleContact>& contacts);
    void addExternalContacts(vector<ParticleContact>& contacts, Particle* other, float restitution);

    //reset the position of the particles
    void spawnBlob(Vector3 centerpos, float radius, int slices, float mass);
    void reset(Vector3 centerpos, float radius, int slices, float mass);

private:
    /// World in which particles are added.
    World& _world;
    /// All particles composing the blob.
    vector<Particle> _particles;
    /// All forces linking particles.
    vector<SpringForceGenerator> _springs;
};