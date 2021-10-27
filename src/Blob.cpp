#include "Blob.hpp"
#include "Phase2/ParticleContact.hpp"
#include "Phase2/ParticleForceGenerator.hpp"

#include <cmath>

#define PI 3.14159f

static float dist(Particle* a, Particle* b) {
    return (a->getPosition() - b->getPosition()).norm();
}

Blob::Blob(World& world, Vector3 centerpos, float radius, int slices, float mass) :
    _world(world)
{

    Vector3 color { 0.0f, 1.0f, 0.5f };
    
    // Indices of  [0]                 = center
    // particles : [1:slices]          = inner skin
    //             [slices+1:2*slices] = outer skin 
    _particles.reserve(2*slices+1);
    
    // Center
    Particle* center = &_particles.emplace_back(mass, centerpos, color, 0.1f, 1.f);
    // Inner skin
    for (int i = 1; i <= slices; ++i) {
        float angle = 2 * PI * i/slices;
        Vector3 pos { radius * 0.8f * cos(angle), radius * 0.8f * sin(angle), 0 };
        _particles.emplace_back(mass, pos + centerpos, color, 0.1f, 1.f);
    }
    // Outer skin
    for (int i = 1; i <= slices; ++i) {
        float angle = 2 * PI * i/slices;
        Vector3 pos { radius * cos(angle), radius * sin(angle), 0 };
        _particles.emplace_back(mass, pos + centerpos, color, 0.1f, 1.f);
    }

    _springs.reserve(5*slices);

    Particle *lastinner = &_particles[slices], *lastouter = &_particles[2*slices];
    for (int i = 1; i <= slices; ++i) {
        // For each i, we have 5 springs:
        Particle *inner = &_particles[i], *outer = &_particles[i+slices];
        // 1/ center   <-> inner[i]
        _springs.emplace_back(center, inner, 20, dist(center, inner));
        // 2/ inner[i] <-> outer[i]
        _springs.emplace_back(inner, outer, 20, dist(inner, outer));
        // 3/ inner[i] <-> inner[i+1]
        _springs.emplace_back(lastinner, inner, 20, dist(lastinner, inner));
        // 4/ outer[i] <-> outer[i+1]
        _springs.emplace_back(lastouter, outer, 20, dist(lastouter, outer));
        // 5/ inner[i] <-> outer[i+1]
        _springs.emplace_back(lastinner, outer, 20, dist(lastinner, outer));

        lastinner = inner; lastouter = outer;
    }
    
    // Add all particles to world.
    for (auto& p : _particles)
        world.particleList.insert(&p);
    // Add all springs to world.
    for (auto& f : _springs)
        world.registerOfForces.insert(&f);

}


void Blob::addInternalContacts(vector<ParticleContact>& contacts) {
    // NOT WORKING
    return;
    
    for (auto& f : _springs) {
        auto [p1,p2] = f.getParticles();
        auto contact = ParticleContact::fromCord(p1, p2, f.getRelaxedLength(), 0);
        if (contact)
            contacts.push_back(*contact);
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