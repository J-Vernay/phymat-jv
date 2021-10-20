#include "../Particle.hpp"
#include "../Vector.hpp"

class ParticleContact
{
private:
    Particle* particle[2];
    float restitution;
    Vector3 normale;
    

public:
    ParticleContact(/* args */);
    ~ParticleContact();

    void resolve();
    float vsCalculation();
    void resolveVelocity();
};


