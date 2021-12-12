#pragma once
#include "../Vector.hpp"

using namespace std;

class Contact {
private :
	Vector3 contactPoint;
	Vector3 contactNormal;
	float penetration;
public :
	Contact(Vector3, Vector3, float);
	Contact();

	Vector3 getContactPoint();
	void setContactPoint(Vector3);
	Vector3 getContactNormal();
	void setContactNormal(Vector3);
	float getPenetration();
	void setPenetration(float);
};