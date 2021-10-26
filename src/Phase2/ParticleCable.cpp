#include "ParticleCable.h"
#include "ParticleContact.hpp"

void ParticleCable::addContact() {
	float length = currentLenght();
	Vector3 normale = particle[0]->getVelocity() - particle[1]->getVelocity();
	if (length >= maxLength){
		ParticleContact contact = new ParticleContact(particles, restitution, normale);
	}
}