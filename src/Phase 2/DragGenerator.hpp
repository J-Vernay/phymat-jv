#include "../Vector.hpp"
#include "ParticleForceGenerator.hpp"

class DragGenerator : public ParticleForceGenerator
{
private:
    float k1;
    float k2;
public:
    //CONSTRUCTORS
    DragGenerator(float k1, float k2);
    DragGenerator(); //k1 = 1, k2 = 2 by default

    void updateForces(Particle *particle, float duration);
    
    //GETTERS & SETTERS
    float getK1();
    float getK2();
    void setDrag(float k1, float k2);
    void setK1(float k1);
    void setK2(float k2);
};



