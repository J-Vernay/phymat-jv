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
        /// Damping used for this particle: amount of velocity kept each frame, simulating friction.
        float damping;
        /// Color of the particle.
        Vector3 color;
        /// Radius of the particle.
        float radius;

    public:
        /// Accumulator of forces for the current frame, which is modified
        /// by force generators each frame.
        Vector3 accumulationOfForces;

        /// Constructs a particle given its initial properties.
        Particle(float mass, Vector3 initialPosition, Vector3 color, float radius, float damping); 

        /// Get position.
        Vector3 getPosition() const { return position; }
        /// Set position.
        void setPosition(Vector3 p) { position = p; }
        /// Get velocity.
        Vector3 getVelocity() const { return velocity; }
        /// Set velocity.
        void setVelocity(Vector3 v) { velocity = v; }
        /// Get damping.
        float getDamping() const { return damping; }
        /// Get inverse of mass.
        float getInverseMass() const { return inverseMass; }
        /// Get mass.
        float getMass() const { return 1/inverseMass; }
        /// Get radius.
        float getRadius() const { return radius; }
        /// Get color.
        Vector3 getColor() const { return color; }

        /// Reset the accumulation forces to zero, should be called at beginning of each frame.
        void resetAccumulationForces();
        /// Integrate the state of the particle, deriving its acceleration from the accumulated forces.
	    void integrate(float time);

        /// Output textual representation of particle.
        friend ostream& operator<<(ostream& os, const Particle&);
};
