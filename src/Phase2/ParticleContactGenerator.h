#include "../Particle.hpp"

using namespace std;

class ParticleContactGenerator {

public:
    virtual void addContact(Particle* particle) = 0;
};