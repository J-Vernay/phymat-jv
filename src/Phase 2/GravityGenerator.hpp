#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class GravityGenerator : public ParticleForceGenerator
{
private:
    Vector3 gravity;
    Particle * particle;
public:
    //CONSTRUCTORS
    GravityGenerator(Particle * particle, Vector3 gravity);
    GravityGenerator(Particle * particle, float gravityConstant);
    GravityGenerator(Particle * particle); //Gravity set to (0,0,-10) by default

    void updateForces(float duration);
    
    //GETTERS & SETTERS
    Vector3 getGravity();
    void setGravity(Vector3 gravity);
    void setGravity(float gravityConstant);
};



