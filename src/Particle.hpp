#pragma once
#include "Vector.hpp"
#include "ExceptionsForParticle.hpp"

using namespace std;


class Particle {       
    private:   //Private attributes of Particle     
        float inverseMass;    // 1/mass of the particle
        Vector3 position;
        Vector3 velocity;
        int type;
        float damping;        // Damping : Percentage of damping of the particle = percentage of velocity kept from one frame to another

    public:       //Public attributes of Particle
        Vector3 acceleration;
        Vector3 accumulationOfForces; //Accumulation of all forces

        //-----FUNCTIONS--------//
        Particle(float, Vector3, Vector3, Vector3, float, int); 

        //Getter & Setter :
        void setPosition(Vector3);
        void setVelocity(Vector3);
        void setAcceleration(Vector3);
        void setType(int);
        Vector3 getAcceleration();
        Vector3 getPosition();
        Vector3 getVelocity();
        float getDamping();
        float getInverseMass();
        float getMass();
        int getType();

        void resetAccumulationForces(); //To reset the forces applied to the particle
	    void integrate(float time);

        //Overload of operators
        friend ostream& operator<<(ostream& os, const Particle&);
};
