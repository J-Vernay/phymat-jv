#include "ParticleCable.h"
#include "ParticleContact.hpp"
//class that simulate a cable collision
void ParticleCable::addContact() {
	float length = currentLength();
	Vector3 normale = particle[0]->getVelocity() - particle[1]->getVelocity();
	if (length >= maxLength){
		ParticleContact* contact = new ParticleContact(particle[0], particle[1], restitution, normale, 0);
	}
}