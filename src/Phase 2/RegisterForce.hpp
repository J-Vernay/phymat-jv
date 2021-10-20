#include "../Vector.hpp"
#include "../Particle.hpp"
#include "ParticleForceGenerator.hpp"
#include <vector>

using namespace std;

class RegisterForces {
    struct RecordingForces
    {
        Particle *particle;
        ParticleForceGenerator *pfg;
    };
    
    vector<RecordingForces> Register;

};