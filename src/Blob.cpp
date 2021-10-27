#include "Blob.hpp"
#include "Phase2/ParticleContact.hpp"

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
        Vector3 pos { radius * cos(angle), radius * sin(angle), 0 };
        Particle* p = &_particles.emplace_back(mass, pos + centerpos, color, 0.1f, 1.f);
        _world.particleList.insert(p);
        ParticleForceGenerator* f = &_springs.emplace_back(center, p, 20, radius);
        _world.registerOfForces.insert(f);
    }

}


void Blob::addInternalContacts(vector<ParticleContact>& contacts) {
    for (int i = 0; i < _particles.size() - 1; ++i) {
        for (int j = i + 1; j < _particles.size(); ++j) {
            auto contact = ParticleContact::fromCollision(&_particles[i], &_particles[j], 1);
            if (contact)
                contacts.push_back(*contact);
        }
    }
}


void Blob::addExternalContacts(vector<ParticleContact>& contacts, Particle* other, float restitution) {
    for (auto& p : _particles) {
        auto contact = ParticleContact::fromCollision(&p, other, restitution);
        if (contact)
            contacts.push_back(*contact);
    }
}

Blob::~Blob() {
    for (auto& p : _particles)
        _world.particleList.erase(&p);
}

void Blob::spawnBlob(Vector3 centerpos, float radius, int slices, float mass){
    Vector3 color { 0.0f, 1.0f, 0.5f };

    _particles.reserve(slices*slices+1);
    _springs.reserve(slices*slices+1);

    Particle* center = &_particles.emplace_back(mass, centerpos, color, 0.1f, 1.f);
    _world.particleList.insert(center);

    for (int i = 0; i < slices; ++i) {
        float angle = 2 * PI * i/slices;
        Vector3 pos { radius * cos(angle), radius * sin(angle), 0 };
        Particle* p = &_particles.emplace_back(mass, pos + centerpos, color, 0.1f, 1.f);
        _world.particleList.insert(p);
        ParticleForceGenerator* f = &_springs.emplace_back(center, p, 20, radius);
        _world.registerOfForces.insert(f);
    }

}

void Blob::reset(Vector3 centerpos, float radius, int slices, float mass){
}