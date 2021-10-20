#include "DragGenerator.hpp"

//Construct a generator with the drag's coefficients put by default at 1
DragGenerator::DragGenerator(){
    this->k1 = 1;
    this->k2 = 1;
}

//Construct a generator with the two drag's coefficients given
DragGenerator::DragGenerator(float k1, float k2){
    this->k1 = k1;
    this->k2 = k2;
}

//Update the force for drag
void DragGenerator::updateForces(Particle *particle, float duration){
    Vector3 dragForce =  (particle->getVelocity().norm() * this->k1 + this->k2 * particle->getVelocity().norm() * particle->getVelocity().norm()) * particle->getVelocity();
    //add force to register
}

//Getter for drag member
float DragGenerator::getK1(){
    return this->k1;
}

//Getter for drag member
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