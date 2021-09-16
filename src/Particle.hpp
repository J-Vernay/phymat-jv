#pragma once
#include "Vector.hpp"
#include "ExceptionsForParticle.hpp"

using namespace std;


class Particle {       
    private:   //Private attributes of Particle     
        float inverseMass;    // 1/mass of the particle
        Vector3 position;
        Vector3 velocity;
        float damping;        // Damping : Percentage of damping of the particle

    public:       //Public attributes of Particle
        Vector3 acceleration;

        //-----FUNCTIONS--------//
        Particle(float, Vector3, Vector3, Vector3, float); 

        //Getter & Setter :
        void setAcceleration(Vector3);
        Vector3 getAcceleration();
        Vector3 getPosition();
        Vector3 getVelocity();
        float getDamping();
        float getInverseMass();
        float getMass();

        //Overload of operators
        friend ostream& operator<<(ostream& os, const Particle&);

};

//Constructor
Particle::Particle(float mass, Vector3 initialPosition, Vector3 initialVelocity, Vector3 initialAcceleration, float damping){
    if(mass == 0){
        //inverseMass = inf
        throw ExceptionInverseMassInf;
    }
    else if(mass == -1){ // Lets say -1 <=> infinity
        this->inverseMass = 0;
    }
    else if (mass < 0 && mass != -1){
        //mass cannot be negativ
        throw ExceptionNegativMass;
    }
    else {
        this->inverseMass = 1 / mass;
    }
    this->position = initialPosition;
    this->velocity = initialVelocity;
    this->acceleration = initialAcceleration;

    if(damping > 1 || damping < 0){
        //error damping is not a pourcentage
        throw ExceptionDampingNotPercentage;
    }
    else {
        this->damping = damping;
    }
}

//Getter & Setters :
void Particle::setAcceleration(Vector3 newAcceleration){
    this->acceleration = newAcceleration;
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

//Overload of << 
ostream& operator<<(ostream& os, const Particle& P){
    os << "======== Particle ========\n" << "Mass : " << 1/P.inverseMass << "\nPosition : \n" << P.position << "\nVelocity : \n" << P.velocity << "\nAcceleration :\n" << P.acceleration << "\nDamping : " << P.damping << endl;
    return os;
}