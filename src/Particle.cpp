#include "Particle.hpp"

//Constructor
Particle::Particle(float mass, Vector3 initialPosition, Vector3 initialVelocity, float damping, int type){
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
    this->velocity = initialVelocity;

    if(damping > 1 || damping < 0){
        //error damping is not a pourcentage
        throw ExceptionDampingNotPercentage();
    }
    else {
        this->damping = damping;
    }

    this->type = type;

    this->accumulationOfForces = Vector3(0, 0, 0);
}

//Getter & Setters :
void Particle::setPosition(Vector3 newPosition){
    position = newPosition;
}

void Particle::setVelocity(Vector3 newVelocity){
    velocity = newVelocity;
}

void Particle::setType(int newType){
    this->type = newType;
}

Vector3 Particle::getPosition() const {
    return this->position;
}

Vector3 Particle::getVelocity() const {
    return this->velocity;
}

float Particle::getDamping() const {
    return this->damping;
}

float Particle::getInverseMass() const {
    return this->inverseMass;
}

float Particle::getMass() const {
    if(this->inverseMass == 0){
        return -1;
    }
    else return 1/this->inverseMass;
}

int Particle::getType() const {
    return type;
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
