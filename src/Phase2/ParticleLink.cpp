#include "ParticleLink.h"

float ParticleLink::currentLength() const {
	Vector3 posA = particle[0]->getPosition();
	Vector3 posB = particle[1]->getPosition();
	Vector3 diff = posA - posB;
	float length = norm(diff);
	return length;
}