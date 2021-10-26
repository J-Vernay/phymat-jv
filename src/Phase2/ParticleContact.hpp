#pragma once

#include "../Particle.hpp"
#include "../Vector.hpp"

// Forward declaration to prevent cyclic dependency between include files.
class ParticleContactResolver;

class ParticleContact
{
private:
    Particle* particle[2];
    float restitution;
    Vector3 normale;
    friend class ParticleContactResolver;

    

public:
    ParticleContact(/* args */);
    ~ParticleContact();

    void resolve(float);
    float vsCalculation();
    void resolveVelocity(float);
    void resolveInterpenetration();
};


