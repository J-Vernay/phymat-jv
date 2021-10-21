#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class SpringForceGenerator : public ParticleForceGenerator
{
private:
    Particle* particleA;
    Particle* particleB;
    float elasticity; //elasticity (N/m)
    float relaxedLength; //relaxed length (m)
public:
    //CONSTRUCTORS
    SpringForceGenerator(Particle *particleA, Particle *particleB, float k, float l0);
    SpringForceGenerator(Particle *particleA, Particle *particleB); //k = 20, l0 = 1 by default

    void updateForces(float duration); //update the force accumulator of the particle by adding the force associated to the spring
    
    //GETTERS & SETTERS
    float getElasticity();
    float getRelaxedLength();
    void setElasticity(float k);
    void setRelaxedLength(float l0);
};
