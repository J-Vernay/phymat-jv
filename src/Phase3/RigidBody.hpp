#pragma once

#include "../Particle.hpp"

class RigidBody
{
private:
    Particle massCenter;
public:
    RigidBody(/* args */);

    void setMassCenter(Particle);
    Particle getMassCenter();
};


