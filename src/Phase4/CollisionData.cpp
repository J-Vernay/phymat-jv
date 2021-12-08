#include "CollisionData.h"

CollisionData::CollisionData(Contact* newContact, int newRemainingContacts) {
	contacts = newContact;
	remainingContacts = newRemainingContacts;
};

Contact* CollisionData::getContacts() {
	return contacts;
};

void CollisionData::setContacts(Contact* newContacts) {
	contacts = newContacts;
};

int CollisionData::getRemainingContacts() {
	return remainingContacts;
};

void CollisionData::setRemainingContacts(int newRemainingContacts) {
	remainingContacts = newRemainingContacts;
};