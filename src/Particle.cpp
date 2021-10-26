#include "Particle.hpp"

//Constructor
Particle::Particle(float mass, Vector3 initialPosition, Vector3 color, float radius, float damping) :
    color(color), radius(radius)
{
    if(mass == 0){
        //inverseMass = inf
        throw ExceptionInverseMassInf();
    }
    else if(mass == -1){ // Lets say -1 <=> infinity
        this->inverseMass = 0;
    }
    else if (mass < 0 && mass != -1){
        //mass cannot be negativ
        throw ExceptionNegativMass();
    }
    else {
        this->inverseMass = 1 / mass;
    }
    this->position = initialPosition;

    if(damping > 1 || damping < 0){
        //error damping is not a pourcentage
        throw ExceptionDampingNotPercentage();
    }
    else {
        this->damping = damping;
    }
}

void Particle::resetAccumulationForces() {
    accumulationOfForces = Vector3(0, 0, 0);
}
void Particle::integrate(float time) {
    Vector3 acceleration = accumulationOfForces * inverseMass;
    position = (position + velocity * time + acceleration * time * time / 2);
    velocity = velocity + acceleration * time;
}


//Overload of << 
ostream& operator<<(ostream& os, const Particle& P){
    os << "======== Particle ========\n" << "Mass : " << 1/P.inverseMass << "\nPosition : \n" << P.position << "\nVelocity : \n" << P.velocity << "\nDamping : " << P.damping << endl;
    return os;
}
