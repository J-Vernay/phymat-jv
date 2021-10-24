#include "Integrator.hpp"

//Constructor
//Default : gravity = 10, particleList empty, frameRate = 60 fps
Integrator::Integrator() {
    gravity = Vector3(0,0,-10);
    frameRate = 60;
    if (frameRate == 0) {
        time = 1;
    }
    else{
        time = 1/abs(frameRate);
    }
}

//Getters
Vector3 Integrator::getGravity(){
    return gravity;
}

vector<Particle> Integrator::getParticleList(){
    return particleList;
}

double Integrator::getFrameRate(){
    return frameRate;
}


//Setters
void Integrator::setGravity(Vector3 newGravity){
    gravity = newGravity;
}
void Integrator::setParticleList(vector<Particle> newParticleList){
    particleList = newParticleList;
}
void Integrator::setFrameRate(double newFrameRate){
    if(frameRate > 0){
        frameRate = newFrameRate;
    }
    else {
        throw ExceptionNegativOrNullFramerate();
    }

}

//Useful Functions
void Integrator::addParticle(Particle p){
    particleList.push_back(p);
}

// Add a particle at the index given
void Integrator::addParticleAtIndex(Particle P, int idx){
    if(idx < particleList.size() && idx >= 0){
        particleList.insert(particleList.begin() + idx, P);
    }
    else{ // If the index is superior at the particle list size, add the particle at the end
        particleList.push_back(P);
    }
}

// Delete the particle at the index given
void Integrator::deleteParticleAt(int idx){
    if(idx < particleList.size() && idx >= 0){
        particleList.erase(particleList.begin() + idx);
    }
    else {
        throw ExceptionDeleteIndexOutOfRange();
    }
}

// Delete the last particle of the list
void Integrator::deleteLastParticle(){
    if(particleList.size() > 0){
        particleList.pop_back();
    }
    else {
        throw ExceptionDeleteIndexOutOfRange();
    }
}


//Update position, velocity and acceleration + clear all out the map particles
void Integrator::updateAll(){
    for(auto &p : particleList){
        p.acceleration = gravity;
        p.integrate(time);
    }
    clearParticleList();
}


//Delete particle if is under the ground
void Integrator::clearParticleList(){
    vector<int> idxParticleToClear;
    //find every particle to clear and store the index
    for(int idx = 0; idx < particleList.size(); idx++){
        if (particleList[idx].getPosition().getz() <= 0){
            idxParticleToClear.push_back(idx);
        }
    }

    //Clear the particle list
    int counterOfCleared = 0;
    for (int i : idxParticleToClear){
        deleteParticleAt(i-counterOfCleared);
        counterOfCleared++;
    }
}

//Get Particle at the index given
Particle Integrator::getParticleAt(int index){
    if(index < this->getParticleList().size()){
            return this->getParticleList()[index];
    }
    else {
        throw ExceptionDeleteIndexOutOfRange();
    }
}

//Main function to update all forces to all particles
void Integrator::integrate(){
    for(auto &p : particleList){ //add gravity force to each particle
        GravityGenerator(&p).updateForces(1/this->frameRate);
    }
    for(ParticleForceGenerator &force : registerOfForces){ //add all the other forces contained in the register
        force.updateForces(1/this->frameRate); 
    }
    this->updateAll(); //update the position of each particle

}

//Overload of << 
ostream& operator<<(ostream& os, const Integrator& I){
    os << "======== Integrator ========\n" << "Framerate : " << I.frameRate << "\nGravity : " << I.gravity << "\nList of Particles : \n" <<  endl;
    for(auto &P : I.particleList){
        os << P << endl;
    }
    return os;
}