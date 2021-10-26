#include "ParticleContact.hpp"

ParticleContact::ParticleContact(/* args */)
{
}

ParticleContact::~ParticleContact()
{
}

//Resolve One contact
void ParticleContact::resolve(float frameDuration){
    resolveInterpenetration();
    resolveVelocity(frameDuration);
}

//Calculate separation speed and returns it
float ParticleContact::vsCalculation(){
    
    //vs = (Va - Vb) * n
    return ((particle[0]->getVelocity() - particle[1]->getVelocity())*normale);
}

//TO DO stationnary particle problem
void ParticleContact::resolveVelocity(float frameDuration){
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
void ParticleContact::resolveInterpenetration(){
    //get distance between the two objects
    float distance = (particle[0]->getPosition()-particle[1]->getPosition()).norm();
    //Code to add when not particles anymore :
    //Check if the particles are penetrating each other
    // if(distance < particle[0]->getRadius()+particle[1]->getRadius()){
    //     float ma,mb;
    //     ma = 1/particle[0]->getInverseMass();
    //     mb = 1/particle[1]->getInverseMass();
    //     //move objects away from each other depending on their mass
    //     particle[0]->setPosition(particle[0]->getPosition()+(distance*mb/(ma+mb))*normale);
    //     particle[1]->setPosition(particle[1]->getPosition()-(distance-distance*mb/(ma+mb))*normale);
    // }
}