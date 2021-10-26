#include "../Particle.hpp"

using namespace std;

/// Class representing an abstract relation betweens particles
/// which may cause collisions = contacts.
class ParticleContactGenerator {

public:
    virtual void addContact(Particle* particle) = 0;
};