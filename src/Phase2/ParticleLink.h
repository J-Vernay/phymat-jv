#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator
{
protected:
	Particle* particle[2];
public:
	float currentLength() const;
};