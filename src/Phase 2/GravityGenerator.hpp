#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class GravityGenerator : public ParticleForceGenerator
{
private:
    Vector3 gravity;
public:
    //CONSTRUCTORS
    GravityGenerator(Vector3 gravity);
    GravityGenerator(float gravityConstant);
    GravityGenerator(); //(0,0,-10) by default

    void updateForces(Particle *particle, float duration);
    
    //GETTERS & SETTERS
    Vector3 getGravity();
    void setGravity(Vector3 gravity);
    void setGravity(float gravityConstant);
};



