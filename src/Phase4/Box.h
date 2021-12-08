#pragma once
#include "../Phase3/RigidBody.hpp"
#include "../Vector.hpp"

using namespace std;

class Box : public RigidBody{
private:
	void setHalfsizes(Vector3);
	Vector3 halfsizes;
public:
	Box(Vector3);

	Vector3 getHalfsizes();
};