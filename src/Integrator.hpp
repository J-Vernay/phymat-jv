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
        void updatePosition();
        void updateFastPosition();
        void updateVelocity();
        void updateAcceleration();
        void clearParticleList();
        Particle getParticleAt(int);
        void updateAll();
        void updateAllFast();

    //Operator Overload
        friend ostream& operator<<(ostream& os, const Integrator&);

};
