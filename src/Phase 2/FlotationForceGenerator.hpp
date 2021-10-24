#pragma once
#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class FlotationForceGenerator : public ParticleForceGenerator
{
private:
    Particle* particle;
    float volume; //will be filled with the particle and with its type
    float maxDepth; //max depth of the environment
    float densityEnvironment; //density of the environment
    float heightEnvironment; //height of th eenvironment
public:
    //CONSTRUCTORS
    FlotationForceGenerator(Particle *particle, float maxDepth, float densityEnvironment, float heightEnvironment);
    FlotationForceGenerator(Particle *particle); //By default : maxDepth = 50 (enough for a lake for ex), densityEnvironment = 0.998 (for water), heightEnvironment = 0 (level of water in most cases)

    void updateForces(float duration); //update the force accumulator of the particle by adding the force associated to the spring
    
    //GETTERS & SETTERS
    float getMaxDepth();
    float getDensityEnvironment();
    float getHeightEnvironment();

    void setMaxDepth(float maxDepth);
    void setDensityEnvironment(float density);
    void setHeightEnvironment(float height);

};
