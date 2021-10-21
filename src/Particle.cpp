#include "Particle.hpp"

//Constructor
Particle::Particle(float mass, Vector3 initialPosition, Vector3 initialVelocity, Vector3 initialAcceleration, float damping, int type){
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
    this->acceleration = initialAcceleration;

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

void Particle::setAcceleration(Vector3 newAcceleration){
    this->acceleration = newAcceleration;
}

void Particle::setType(int newType){
    this->type = newType;
}

Vector3 Particle::getAcceleration(){
    return this->acceleration;
}

Vector3 Particle::getPosition(){
    return this->position;
}

Vector3 Particle::getVelocity(){
    return this->velocity;
}

float Particle::getDamping(){
    return this->damping;
}

float Particle::getInverseMass(){
    return this->inverseMass;
}

float Particle::getMass(){
    if(this->inverseMass == 0){
        return -1;
    }
    else return 1/this->inverseMass;
}

int Particle::getType(){
    return type;
}

void Particle::resetAccumulationForces() {//To reset the forces applied to the particle
    this->accumulationOfForces = Vector3(0, 0, 0);
}

//Overload of << 
ostream& operator<<(ostream& os, const Particle& P){
    os << "======== Particle ========\n" << "Mass : " << 1/P.inverseMass << "\nPosition : \n" << P.position << "\nVelocity : \n" << P.velocity << "\nAcceleration :\n" << P.acceleration << "\nDamping : " << P.damping << endl;
    return os;
}