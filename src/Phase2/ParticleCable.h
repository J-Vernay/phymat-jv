#pragma once
#include "ParticleLink.h"

class ParticleCable : public ParticleLink
{
private :
	float maxLength; //length max of the cable
	float restitution; // restitution rate
public:
	void addContact();
};