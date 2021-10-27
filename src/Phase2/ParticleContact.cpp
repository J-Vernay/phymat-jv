#include "ParticleContact.hpp"

ParticleContact::ParticleContact(Particle* a, Particle* b, float restit, Vector3 normal)
{
    restitution = restit;
    normale = normal / normal.norm();
    particle[0] = a;
    particle[1] = b;

    // First particle characteristics
    Vector3 posA=particle[0]->getPosition();
    float RA = particle[0]->getRadius();
    Vector3 posB=particle[1]->getPosition();
    float RB = particle[1]->getRadius();

    float distance = (posA - posB) * normale; // Center to center distance
    float raysSum = RA + RB; // Distance if the spheres are touching each other with no penetration
    
    if (distance >= raysSum) { // No penetration at all
        penetration = 0;
    }
    else { 
        penetration = (raysSum - distance) ; // Penetration distance
    }
}

ParticleContact::~ParticleContact()
{
}

//Resolve One contact
void ParticleContact::resolve(float frameDuration) const {
    // If both objects are static, no resolution.
    if (particle[0]->getInverseMass() == 0 && particle[1]->getInverseMass() == 0)
        return;
    resolveInterpenetration();
    resolveVelocity(frameDuration);
}

//Calculate separation speed and returns it
float ParticleContact::vsCalculation() const {
    //vs = (Va - Vb) * n
    return ((particle[0]->getVelocity() - particle[1]->getVelocity())*normale);
}

//TO DO stationnary particle problem
void ParticleContact::resolveVelocity(float frameDuration) const {
    //vs' = -C * vs
    float vs1 = vsCalculation(), vs2 = -restitution*vs1;
    
    bool is_static_a = particle[0]->getInverseMass() == 0;
    bool is_static_b = particle[1]->getInverseMass() == 0;

    if (is_static_a) {
        particle[1]->setVelocity(particle[0]->getVelocity() + vs2 * normale);
    } else if (is_static_b) {
        particle[0]->setVelocity(particle[1]->getVelocity() - vs2 * normale);
    } else {
        //Calculate impuls and set it in the normale direction
        float totalmass = particle[0]->getMass() + particle[1]->getMass();
        float impuls = totalmass*(vs2 - vs1);
        Vector3 impulsVec = impuls*normale;
        //update velocities for both particles
        particle[0]->setVelocity(particle[0]->getVelocity() + impulsVec*particle[0]->getInverseMass());
        particle[1]->setVelocity(particle[1]->getVelocity() - impulsVec*particle[1]->getInverseMass());
    }
}

//Resolve Interpenetration in case the 2objects are penetrating each other
//To add when the particles are not particles anymore but objects
void ParticleContact::resolveInterpenetration() const {
    float ma = particle[0]->getMass(), mb = particle[1]->getMass();
    //move objects away from each other depending on their mass
    float factor_a = isinf(mb) ? 1 : mb/(ma+mb); // special case for mb=INF to prevent NaN.
    
    particle[0]->setPosition(particle[0]->getPosition()+(penetration*factor_a)*normale);
    particle[1]->setPosition(particle[1]->getPosition()-(penetration*(1-factor_a))*normale);
}

optional<ParticleContact> ParticleContact::fromCollision(Particle *a, Particle *b, float restitution) {
    Vector3 posdiff = a->getPosition() - b->getPosition();
    float sumradius = a->getRadius() + b->getRadius();
    if (sumradius * sumradius <= posdiff.squareNorm())
        return {}; // No contact
    return ParticleContact(a, b, restitution, posdiff);
}