#pragma once



#include "../Particle.hpp"
#include "../Vector.hpp"
#include "ParticleContactResolver.hpp"

class ParticleContact
{
private:
    Particle* particle[2];
    float restitution;
    Vector3 normale;
    friend ParticleContactResolver;

    

public:
    ParticleContact(/* args */);
    ~ParticleContact();

    void resolve(float);
    float vsCalculation();
    void resolveVelocity(float);
    void resolveInterpenetration();
};


