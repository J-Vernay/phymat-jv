#pragma once

#include <vector>
#include <math.h>

#include "Vector.hpp"
#include "Particle.hpp"
//#include "./Phase 2/RegisterForce.hpp" NOT USED
#include "./Phase 2/GravityGenerator.hpp"
#include "./Phase 2/ParticleForceGenerator.hpp"

#include "ExceptionsForIntegrator.hpp"

using namespace std;

class Integrator {
    private :
        Vector3 gravity;
        vector<Particle> particleList = {};
        double frameRate; //in fps
        double time; //in s
        vector<ParticleForceGenerator> registerOfForces; // /!\ RegisterForce class not used cause only one attribute and need to for auto

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
  
        //Main function to update all forces to all particles
        void integrate();

    //Operator Overload
        friend ostream& operator<<(ostream& os, const Integrator&);

};
