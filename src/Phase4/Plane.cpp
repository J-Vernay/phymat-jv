#include "Plane.h"

Plane::Plane(Particle const& mass_center, Matrix3 inertia, float angdamping, Vector3 newNormale) : RigidBody(mass_center, inertia, angdamping){

	normale = newNormale;
	offset = 0.0;
}

Plane::Plane(Particle const& mass_center, Matrix3 inertia, float angdamping, Vector3 newNormale, float newOffset)  : RigidBody(mass_center, inertia, angdamping){
	normale = newNormale;
	offset = newOffset;
}

Vector3 Plane::getNormale() {
	return normale;
}

void Plane::setNormale(Vector3 newNormale) {
	normale = newNormale;
}

float Plane::getOffset() {
	return offset;
}

void Plane::setOffset(float newOffset) {
	offset = newOffset;
}

