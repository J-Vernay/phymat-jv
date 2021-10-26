#include "ParticleContact.hpp"

ParticleContact::ParticleContact(Particle* particles[2], float restit, Vector3 normal)
{
    restitution = restit;
    normale = normal;
    particle[0] = particles[0];
    particle[1] = particles[1];

    // First particle characteristics
    Vector3 posA=particle[0]->getPosition();
    float RA = particle[0]->getRadius();
    Vector3 posB=particle[1]->getPosition();
    float RB = particle[1]->getRadius();

    float distance = (posB - posA) * normale; // Center to center distance
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
    float mass = 1/particle[0]->getInverseMass() + 1/particle[1]->getInverseMass();
    float vs1,vs2;
    vs1 = vsCalculation();
    //vs' = -C * vs
    vs2 = -restitution*vs1;
    //Calculate impuls and set it in the normale direction
    float impuls = mass*(vs2 - vs1);
    Vector3 impulsVec = impuls*normale;
    //update velocities for both particles
    particle[0]->setVelocity(particle[0]->getVelocity() + impulsVec*particle[0]->getInverseMass());
    particle[1]->setVelocity(particle[1]->getVelocity() - impulsVec*particle[1]->getInverseMass());
}

//Resolve Interpenetration in case the 2objects are penetrating each other
//To add when the particles are not particles anymore but objects
void ParticleContact::resolveInterpenetration() const {
    float ma,mb;
    ma = 1/particle[0]->getInverseMass();
    mb = 1/particle[1]->getInverseMass();
    //move objects away from each other depending on their mass
    particle[0]->setPosition(particle[0]->getPosition()+(penetration*mb/(ma+mb))*normale);
    particle[1]->setPosition(particle[1]->getPosition()-(penetration-penetration*mb/(ma+mb))*normale);
}