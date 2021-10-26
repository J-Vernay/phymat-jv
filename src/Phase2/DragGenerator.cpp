#include "DragGenerator.hpp"

//Construct a generator with the drag's coefficients put by default at 1
DragGenerator::DragGenerator(Particle *particle){
    this->particle = particle;
    this->k1 = 1;
    this->k2 = 1;
}

//Construct a generator with the two drag's coefficients given
DragGenerator::DragGenerator(Particle *particle, float k1, float k2){
    this->particle = particle;
    this->k1 = k1;
    this->k2 = k2;
}

//Update the force for drag
void DragGenerator::updateForces(float duration){
    Vector3 dragForce =  (this->particle->getVelocity().norm() * this->k1 + this->k2 * this->particle->getVelocity().norm() * this->particle->getVelocity().norm()) * this->particle->getVelocity();
    particle->accumulationOfForces += dragForce;
}

//Getter for k1 coeff
float DragGenerator::getK1(){
    return this->k1;
}

//Getter for k2 coeff
float DragGenerator::getK2(){
    return this->k2;
}

//Set the drag member to the drag's coefficient inputs
void DragGenerator::setDrag(float k1, float k2){
    this->k1 = k1;
    this->k2 = k2;
}

//Set the first drag's coefficient 
void DragGenerator::setK1(float k1){
    this->k1 = k1;
}

//Set the second drag's coefficient 
void DragGenerator::setK2(float k2){
    this->k2 = k2;
}