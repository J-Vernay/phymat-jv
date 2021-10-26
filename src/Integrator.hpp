#pragma once

#include <vector>
#include <math.h>

#include "Vector.hpp"
#include "Particle.hpp"
#include "./Phase2/GravityGenerator.hpp"
#include "./Phase2/ParticleForceGenerator.hpp"

#include "ExceptionsForIntegrator.hpp"

using namespace std;

/// Class responsible for storing particles and moving them,
/// applying forces and acceleration upon them.
class Integrator {
    private :
        /// Static gravity applied for all objects whose mass is finite.
        Vector3 gravity;
        /// List of all particles managed by the Integrator.
        vector<Particle> particleList = {};
        /// Time between each frame, in second.
        double deltaTime;
        /// All force generators are stored here. A seperate class was not used
        /// because it would have only one member, and vector provides neat syntax.
        vector<ParticleForceGenerator> registerOfForces;

    public :
        /// Constructs an empty Integrator (with no particles and no force generators).
        Integrator();

    // Getters
        Vector3 getGravity() const;
        vector<Particle> getParticleList() const;
        double getFrameRate() const;

    // Setters
        void setGravity(Vector3);
        void setParticleList(vector<Particle>);
        void setFrameRate(double);

    // Utility function for particle manipulation.
        void addParticle(Particle);
        void addParticleAtIndex(Particle, int);
        void deleteParticleAt(int);
        void deleteLastParticle();
        void clearParticleList();
        Particle getParticleAt(int);

        /// Main function to apply all forces to all particles
        /// and move them according to them.
        void integrate();

        /// Output textual representation of Integrator.
        friend ostream& operator<<(ostream& os, const Integrator&);

};
