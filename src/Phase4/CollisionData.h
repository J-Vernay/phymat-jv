#pragma once
#include "Contact.h"

using namespace std;

class CollisionData {
private:
	Contact* contacts; 
	int remainingContacts;
public:
	CollisionData(Contact*, int);

	Contact* getContacts();
	void setContacts(Contact*);
	int getRemainingContacts();
	void setRemainingContacts(int);
};