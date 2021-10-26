#include "Blob.hpp"

#include <cmath>

#define PI 3.14159f

Blob::Blob(World& world, Vector3 centerpos, float radius, int slices, float mass) :
    _world(world)
{
    Vector3 color { 0.0f, 1.0f, 0.5f };

    _particles.reserve(slices*slices+1);
    _springs.reserve(slices*slices+1);

    Particle* center = &_particles.emplace_back(mass, centerpos, color, 0.1f, 1.f);
    _world.particleList.insert(center);

    for (int i = 0; i < slices; ++i) {
        float angle = 2 * PI * i/slices;
        Vector3 pos { cos(angle), sin(angle), 0 };
        Particle* p = &_particles.emplace_back(mass, pos + centerpos, color, 0.1f, 1.f);
        _world.particleList.insert(p);
        ParticleForceGenerator* f = &_springs.emplace_back(center, p, 1, radius);
        _world.registerOfForces.insert(f);
    }

}

Blob::~Blob() {
    for (auto& p : _particles)
        _world.particleList.erase(&p);
}