#pragma once

#include <vector>
#include <math.h>

#include "Vector.hpp"
#include "Particle.hpp"

using namespace std;

//TO DO acceleration update


class Integrator {
    private :
        double gravity;
        vector<Particle> particleList = {};
        double frameRate; //in fps
        double time; //in s

    public :
    //Constructor
        Integrator();

    //Getters
        double getGravity();
        vector<Particle> getParticleListe();
        double getFrameRate();

    //Setters
        void setGravity(double);
        void setParticleList(vector<Particle>);
        void setFrameRate(double);

    //Useful functions
        void addParticle(Particle);
        //void addParticleAtIndex(Particle, int);
        //void deleteParticle(int);
        void deleteLastParticle();
        float scalarProduct(Vector3, Vector3);
        Vector3 vectorialProduct(Vector3, Vector3);
        float norm(Vector3);
        void updatePosition();
        void updateVelocity();
};

//Constructor
//Default : gravity = 10, particleList empty, frameRate = 60 fps
Integrator::Integrator(){
    gravity = 10;
    frameRate = 60;
    if (frameRate == 0){
        time = 1;
    }
    else{
        time = 1/abs(frameRate);
    }
}

//Getters
double Integrator::getGravity(){
    return gravity;
}

vector<Particle> Integrator::getParticleListe(){
    return particleList;
}

double Integrator::getFrameRate(){
    return frameRate;
}


//Setters
void Integrator::setGravity(double newGravity){
    gravity = newGravity;
}
void Integrator::setParticleList(vector<Particle> newParticleList){
    particleList = newParticleList;
}
void Integrator::setFrameRate(double newFrameRate){
    frameRate = newFrameRate;
}

//Useful Functions
void Integrator::addParticle(Particle p){
    particleList.push_back(p);
}

// void Integrator::addParticleAtIndex(Particle P, int idx){
//     if(idx < particleList.size() && idx >= 0){

//     }
//     else{
//         particleList.push_back(P);
//     }
//}

// void Integrator::deleteParticle(int idx){

// }

void Integrator::deleteLastParticle(){
    particleList.pop_back();
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


//v1 = v0*d^t + a0*t
void Integrator::updateVelocity(){
    for(auto p : particleList){
        float newX = p.getVelocity().getx()*pow(p.getDamping(),time) + p.getAcceleration().getx()*time;
        float newY = p.getVelocity().gety()*pow(p.getDamping(),time) + p.getAcceleration().gety()*time;
        float newZ = p.getVelocity().getz()*pow(p.getDamping(),time) + p.getAcceleration().getz()*time;
        p.setVelocity(Vector3(newX, newY, newZ));
    }
}