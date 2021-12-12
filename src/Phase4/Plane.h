#pragma once
#include "../Vector.hpp"
#include "../Phase3/RigidBody.hpp"

using namespace std;

class Plane : public RigidBody{
	private:
		Vector3 normale;
		float offset;
	public:
		Plane(Particle const& mass_center, Matrix3 inertia, float angdamping, Vector3);
		Plane(Particle const& mass_center, Matrix3 inertia, float angdamping, Vector3, float);

		Vector3 getNormale();
		void setNormale(Vector3);
		float getOffset();
		void setOffset(float);

};