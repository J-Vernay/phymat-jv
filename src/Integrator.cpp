#include "Integrator.hpp"

//Constructor
//Default : gravity = 10, particleList empty, frameRate = 60 fps
Integrator::Integrator() {
    gravity = Vector3(0,0,-10);
    deltaTime = 1/60.f;
}

//Getters
Vector3 Integrator::getGravity() const {
    return gravity;
}

vector<Particle> Integrator::getParticleList() const {
    return particleList;
}

double Integrator::getFrameRate() const {
    return 1/deltaTime;
}


//Setters
void Integrator::setGravity(Vector3 newGravity){
    gravity = newGravity;
}
void Integrator::setParticleList(vector<Particle> newParticleList){
    particleList = newParticleList;
}
void Integrator::setFrameRate(double newFrameRate){
    if(newFrameRate > 0){
        deltaTime = 1/newFrameRate;
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

void Integrator::integrate() {
    // Initialize all particles, and apply gravity.
    for(auto &p : particleList) {
        p.resetAccumulationForces();
        GravityGenerator(&p).updateForces(deltaTime);
    }
    // Apply all registed forces to their respective particles.
    for(ParticleForceGenerator &force : registerOfForces) {
        force.updateForces(deltaTime); 
    }
    // Update acceleration, velocity and position according to accumulated forces.
    for (auto&p : particleList) {
        p.integrate(deltaTime);
    }
}

//Overload of << 
ostream& operator<<(ostream& os, const Integrator& I){
    os << "======== Integrator ========\n" << "Framerate : " << I.getFrameRate() << "\nGravity : " << I.gravity << "\nList of Particles : \n" <<  endl;
    for(auto &P : I.particleList){
        os << P << endl;
    }
    return os;
}