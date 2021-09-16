#pragma once
using namespace std;

#include "Vector.hpp"

class Particle {       
    private:           
        float inverseMass;  
        Vector3 position;
        Vector3 velocity;
        float damping;        // Damping : 

    public:
        Vector3 acceleration;
        Particle(float, Vector3, Vector3, Vector3, float);
        

};

Particle::Particle(float mass, Vector3 initialPosition, Vector3 initialVelocity, Vector3 initialAcceleration, float damping){
    if(mass == 0){
        //inverseMass = inf
    }
    else if(mass == -1){ // Lets say -1 <=> infinity
        this->inverseMass = 0;
    }
    else if (mass < 0 && mass != -1){
        //mass cannot be negativ
    }
    else {
        this->inverseMass = 1 / mass;
    }
    this->position = initialPosition;
    this->velocity = initialVelocity;
    this->acceleration = initialAcceleration;

    if(damping > 1 || damping < 0){
        //error damping is not a pourcentage
    }
    else {
        this->damping = damping;
    }

}

