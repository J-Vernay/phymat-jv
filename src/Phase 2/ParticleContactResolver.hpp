#pragma once

#include <vector>

#include "../Particle.hpp"
#include "../Vector.hpp"
#include "ParticleContact.hpp"

using namespace std;

class ParticleContactResolver
{
private:
    friend ParticleContact;
    int iteration;
    int usedIteration;
    /* data */

public:
    ParticleContactResolver(/* args */);
    ~ParticleContactResolver();
    void resolveContact(vector<ParticleContact>, float);
    void setIteration(int);
    
};

