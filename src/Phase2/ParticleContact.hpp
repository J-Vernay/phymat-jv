#pragma once

#include "../Particle.hpp"
#include "../Vector.hpp"

#include <optional>

// Forward declaration to prevent cyclic dependency between include files.
class ParticleContactResolver;

class ParticleContact
{
private:
    Particle* particle[2];
    float restitution;
    Vector3 normale;
    float penetration;
    friend class ParticleContactResolver;

public:
    /// Constructs a particle contact.
    ParticleContact(Particle* a, Particle* b, float restit, Vector3 normal, float penetration);
    /// Destructor.
    ~ParticleContact();

    /// Create a particle contact from two colliding particles.
    /// If the two particles are not colliding, return `std::nullopt`.
    static optional<ParticleContact> fromCollision(Particle* a, Particle* b, float restitution);

    /// Create a particle contact from two particles in a cord relation.
    /// If the two particles do not need contact correction, return `std::nullopt`.
    static optional<ParticleContact> fromCord(Particle* a, Particle* b, float cordlength, float restitution);

    void resolve(float) const;
    float vsCalculation() const;
    void resolveVelocity(float) const;
    void resolveInterpenetration() const;
};


