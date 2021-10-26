#include "ParticleLink.h"

class ParticleRod : public ParticleLink
{
private : 
	float length; // length of the rod
public :
	void addContact();
};