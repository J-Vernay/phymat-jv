#include "RigidBody.hpp"

RigidBody::RigidBody(){

}

void RigidBody::setMassCenter(Particle massCenterParticle) {
	this->massCenter = massCenterParticle;
};
Particle RigidBody::getMassCenter() {
	return massCenter;
};