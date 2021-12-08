#include "Contact.h"

Contact::Contact(Vector3 newContactPoint, Vector3 newContactNormal, float newPenetration) {
	contactPoint = newContactPoint;
	contactNormal = newContactNormal;
	penetration = newPenetration;
};

Vector3 Contact::getContactPoint(){
	return contactPoint;
};

void Contact::setContactPoint(Vector3 newContactPoint) {
	contactPoint = newContactPoint;
};

Vector3 Contact::getContactNormal() {
	return contactNormal;
};

void Contact::setContactNormal(Vector3 newContactNormal) {
	contactNormal = newContactNormal;
};

float Contact::getPenetration() {
	return penetration;
};

void Contact::setPenetration(float newPenetration) {
	penetration = newPenetration;
};