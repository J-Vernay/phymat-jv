#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
private :
	Particle* particle[2];
public:
	float currentLength() const;
};