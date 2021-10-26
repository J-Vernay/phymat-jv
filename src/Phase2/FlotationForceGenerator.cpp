#include "FlotationForceGenerator.hpp"
#include <stdlib.h>

#define PI 3.14159265358979323846  // PI

//Construct a generator with the drag's coefficients put by default at 1
FlotationForceGenerator::FlotationForceGenerator(Particle *particle){ //By default : maxDepth = 50 (enough for a lake for ex), volume = 1, densityEnvironment = 0.998 (for water), heightEnvironment = 0 (level of water in most cases)
    this->particle = particle;
    this->maxDepth = 50;  //maxDepth of the environment
    this->volume = 1; //volume of the particle
    this->densityEnvironment = 0.998; //Density of the environment (here water)
    this->heightEnvironment = 0; //Level of water most of the time

}

//Construct a generator with the two drag's coefficients given
FlotationForceGenerator::FlotationForceGenerator(Particle *particle, float maxDepth, float densityEnvironment, float heightEnvironment){
    this->particle = particle;
    this->maxDepth = maxDepth;  //maxDepth of the environment
    
    float r = particle->getRadius();
    this->volume = PI * r * r * r * 4.f / 3;
    
    this->densityEnvironment = densityEnvironment; //Density of the environment
    this->heightEnvironment = heightEnvironment; //Level of water most of the time
}

//Update the force accumulator of the particle by adding the force associated to the spring
void FlotationForceGenerator::updateForces(float duration){
    if(particle->getPosition().getz() > this->heightEnvironment + volume * 3/4 *1/PI){ //out of the environment
        //No foces applied, outside the environment
    }
    else if (particle->getPosition().getz() <= this->heightEnvironment - volume * 3/4 *1/PI){ //totally submerged
        particle->accumulationOfForces += volume * densityEnvironment * Vector3(0, 0, 1);// * gravity
    }
    else { //partially submerged
        float submertionPercentage = abs(particle->getPosition().getz() - heightEnvironment - volume * 3/4 * 1/PI);
        particle->accumulationOfForces += submertionPercentage * volume * densityEnvironment * Vector3(0, 0, 1);// * gravity
    }
}

//Getter for elasticity
float FlotationForceGenerator::getDensityEnvironment(){
    return this->densityEnvironment;
}

//Getter for relaxed length
float FlotationForceGenerator::getHeightEnvironment(){
    return this->heightEnvironment;
}

//Set the elasticity
void FlotationForceGenerator::setHeightEnvironment(float height){
    this->heightEnvironment = height;
}

//Set the relaxed length
void FlotationForceGenerator::setDensityEnvironment(float density){
    this->densityEnvironment = density;
}