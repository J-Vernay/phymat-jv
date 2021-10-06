#include "../Vector.hpp"
#include "../Particle.hpp"

using namespace std;

class ParticleForceGenerator {       
    
    public:       //Public attributes of Particle
        virtual void updateForces(Particle *particle, float duration) = 0;
};