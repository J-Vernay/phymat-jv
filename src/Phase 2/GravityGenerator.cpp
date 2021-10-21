#include "GravityGenerator.hpp"

//Construct a generator with the graivty put to (0,0,-10) by default
GravityGenerator::GravityGenerator(Particle *particle){
    this->particle = particle;
    this->gravity = Vector3(0,0,-10);
}

//Construct a generator with the gravity worth to the inut gravity vector
GravityGenerator::GravityGenerator(Particle * particle, Vector3 gravity){
    this->particle = particle;
    this->gravity = gravity;
}

//Construct a generator with a gravity equal to a vector null but in z which is worth the gravityConstant input
GravityGenerator::GravityGenerator(Particle *particle, float gravityConstant){
    this->particle = particle;
    this->gravity = Vector3(0,0,gravityConstant);
}

//Update the force for gravity
void GravityGenerator::updateForces(float duration){
    Vector3 gravityForce = this->gravity * this->particle->getMass();
    //Add force to register
}

//Getter for gravity member
Vector3 GravityGenerator::getGravity(){
    return this->gravity;
}

//Set the gravity member to the gravity vector input
void GravityGenerator::setGravity(Vector3 gravity){
    this->gravity = gravity;
}
    
//Set the gravity member to a vector null but in z which is worth the gravityConstant input
void GravityGenerator::setGravity(float gravityConstant){
    this->setGravity(Vector3 (0, 0, gravityConstant));
}