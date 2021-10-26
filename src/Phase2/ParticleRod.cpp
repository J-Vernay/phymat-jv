#include "ParticleRod.h"

void ParticleRod::addContact() {
	Vector3 normale = particle[0]->getVelocity() - particle[1]->getVelocity();
	//ParticleContact contact = new ParticleContact(particle, 0, normale);
}