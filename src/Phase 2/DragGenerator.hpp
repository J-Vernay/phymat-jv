#pragma once

#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class DragGenerator : public ParticleForceGenerator
{
private:
    Particle* particle;
    float k1;
    float k2;
public:
    //CONSTRUCTORS
    DragGenerator(Particle *particle, float k1, float k2);
    DragGenerator(Particle* particle); //k1 = 1, k2 = 2 by default

    void updateForces(float duration);
    
    //GETTERS & SETTERS
    float getK1();
    float getK2();
    void setDrag(float k1, float k2);
    void setK1(float k1);
    void setK2(float k2);
};



