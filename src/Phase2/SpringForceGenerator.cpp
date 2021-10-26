#include "SpringForceGenerator.hpp"

//Construct a generator with the drag's coefficients put by default at 1
SpringForceGenerator::SpringForceGenerator(Particle *particleA, Particle *particleB){
    this->particleA = particleA;
    this->particleB = particleB;
    this->elasticity = 20;  //elasticity (N/m)
    this->relaxedLength = 1; //relaxed length (m)
}

//Construct a generator with the two drag's coefficients given
SpringForceGenerator::SpringForceGenerator(Particle *particleA, Particle *particleB, float k, float l0){
    this->particleA = particleA;
    this->particleB = particleB;
    this->relaxedLength = l0;
    this->elasticity = k;
}

//Update the force accumulator of the particle by adding the force associated to the spring
void SpringForceGenerator::updateForces(float duration){
    float length = (particleA->getPosition() - particleB->getPosition()).norm(); //length of the spring
    particleA->accumulationOfForces += this->elasticity * (this->relaxedLength - length) * Vector3(0, 0, 1); //applied on z component
    particleB->accumulationOfForces += -this->elasticity * (this->relaxedLength - length) * Vector3(0, 0, 1); //applied on z component
}

//Getter for elasticity
float SpringForceGenerator::getElasticity(){
    return this->elasticity;
}

//Getter for relaxed length
float SpringForceGenerator::getRelaxedLength(){
    return this->relaxedLength;
}

//Set the elasticity
void SpringForceGenerator::setElasticity(float k){
    this->elasticity = k;
}

//Set the relaxed length
void SpringForceGenerator::setRelaxedLength(float l0){
    this->relaxedLength = l0;
}