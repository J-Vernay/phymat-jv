#pragma once
#include "Vector.hpp"
#include "ExceptionsForParticle.hpp"

using namespace std;

/// Class representing a single particle of the world (mass + point).
class Particle {       
    private: 
        /// 1 / mass of the particle, 0 for infinite mass = static object.  
        float inverseMass;
        /// Position of the particle.
        Vector3 position;
        /// Velocity of the particle.
        Vector3 velocity;
        /// Type of particle, determining how it is rendered.
        int type;
        /// Damping used for this particle: amount of velocity kept each frame, simulating friction.
        float damping;

    public:
        /// Accumulator of forces for the current frame, which is modified
        /// by force generators each frame.
        Vector3 accumulationOfForces;

        /// Constructs a particle given its initial properties.
        Particle(float mass, Vector3 initialPosition, Vector3 initialVelocity, float damping, int type); 

        //Getter & Setter :
        void setPosition(Vector3);
        Vector3 getPosition() const;
        void setVelocity(Vector3);
        Vector3 getVelocity() const;

        void setType(int);
        int getType() const;
        float getDamping() const;
        float getInverseMass() const;
        float getMass() const;

        /// Reset the accumulation forces to zero, should be called at beginning of each frame.
        void resetAccumulationForces();
        /// Integrate the state of the particle, deriving its acceleration from the accumulated forces.
	    void integrate(float time);

        /// Output textual representation of particle.
        friend ostream& operator<<(ostream& os, const Particle&);
};
