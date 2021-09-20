#pragma once

#include <vector>
#include <math.h>

#include "Vector.hpp"
#include "Particle.hpp"

#include "ExceptionsForIntegrator.hpp"

using namespace std;

class Integrator {
    private :
        Vector3 gravity;
        vector<Particle> particleList = {};
        double frameRate; //in fps
        double time; //in s

    public :
    //Constructor
        Integrator();

    //Getters
        Vector3 getGravity();
        vector<Particle> getParticleList();
        double getFrameRate();

    //Setters
        void setGravity(Vector3);
        void setParticleList(vector<Particle>);
        void setFrameRate(double);

    //Useful functions
        void addParticle(Particle);
        void addParticleAtIndex(Particle, int);
        void deleteParticleAt(int);
        void deleteLastParticle();
        float scalarProduct(Vector3, Vector3);
        Vector3 vectorialProduct(Vector3, Vector3);
        float norm(Vector3);
        void updatePosition();
        void updateFastPosition();
        void updateVelocity();
        void updateAcceleration();
        void clearParticleList();

    //Operator Overload
        friend ostream& operator<<(ostream& os, const Integrator&);

};

//Constructor
//Default : gravity = 10, particleList empty, frameRate = 60 fps
Integrator::Integrator(){
    gravity = Vector3(0,0,-10);
    frameRate = 60;
    if (frameRate == 0){
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
        throw ExceptionNegativOrNullFramerate;
    }

}

//Useful Functions
void Integrator::addParticle(Particle p){
    particleList.push_back(p);
}

void Integrator::addParticleAtIndex(Particle P, int idx){
    if(idx < particleList.size() && idx >= 0){
        particleList.insert(particleList.begin() + idx, P);
    }
    else{
        particleList.push_back(P);
    }
}

void Integrator::deleteParticleAt(int idx){
    if(idx < particleList.size() && idx >= 0){
        particleList.erase(particleList.begin() + idx);
    }
    else {
        throw ExceptionDeleteIndexOutOfRange;
    }
}

void Integrator::deleteLastParticle(){
    if(particleList.size() > 0){
        particleList.pop_back();
    }
    else {
        throw ExceptionDeleteIndexOutOfRange;
    }
}

float Integrator::scalarProduct(Vector3 v1, Vector3 v2){
    return v1.getx()*v2.getx() + v1.gety()*v2.gety() + v1.getz()*v2.getz();
}

Vector3 Integrator::vectorialProduct(Vector3 v1, Vector3 v2){
    return Vector3(v1.gety()*v2.getz()-v1.getz()*v2.gety(), v1.getz()*v2.getx()-v1.getx()*v2.getz(), v1.getx()*v2.gety()-v1.gety()*v2.getx());
}

float Integrator::norm(Vector3 v){
    return pow(pow(v.getx(),2)+pow(v.gety(),2)+pow(v.getz(),2),0.5);
}

//p1 = p0 + v0*t + a0*(t^2)/2
void Integrator::updatePosition(){
    for(auto p : particleList){
        float newX = p.getPosition().getx() + p.getVelocity().getx()*time + p.getAcceleration().getx()*pow(time, 2)/2;
        float newY = p.getPosition().gety() + p.getVelocity().gety()*time + p.getAcceleration().gety()*pow(time, 2)/2;
        float newZ = p.getPosition().getz() + p.getVelocity().getz()*time + p.getAcceleration().getz()*pow(time, 2)/2;
        p.setPosition(Vector3(newX, newY, newZ));
    }
}

//p1 = p0 + v0*t car a0*(t^2)/2 << p0 + v0*t
void Integrator::updateFastPosition(){
    for(auto p : particleList){
        float newX = p.getPosition().getx() + p.getVelocity().getx()*time;
        float newY = p.getPosition().gety() + p.getVelocity().gety()*time;
        float newZ = p.getPosition().getz() + p.getVelocity().getz()*time;
        p.setPosition(Vector3(newX, newY, newZ));
    }
}

//v1 = v0*d^t + a0*t
void Integrator::updateVelocity(){
    for(auto p : particleList){
        float newX = p.getVelocity().getx()*pow(p.getDamping(),time) + p.getAcceleration().getx()*time;
        float newY = p.getVelocity().gety()*pow(p.getDamping(),time) + p.getAcceleration().gety()*time;
        float newZ = p.getVelocity().getz()*pow(p.getDamping(),time) + p.getAcceleration().getz()*time;
        p.setVelocity(Vector3(newX, newY, newZ));
    }
}

//Update acceleration with gravity
//If particle hits the ground, acceleration is 0 (the ground z is 0)
void Integrator::updateAcceleration(){
    for(auto p : particleList){
        p.acceleration = p.acceleration + gravity*time;
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

//Overload of << 
ostream& operator<<(ostream& os, const Integrator& I){
    os << "======== Integrator ========\n" << "Framerate : " << I.frameRate << "\nGravity : " << I.gravity << "\nList of Particles : \n" <<  endl;
    for(auto P : I.particleList){
        os << P << endl;
    }
    return os;
}