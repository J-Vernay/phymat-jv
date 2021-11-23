#include "RigidBody.hpp"

RigidBody::RigidBody(Particle newMassCenter, Matrix3 newInertia, float newAngDamping) :
	massCenter(newMassCenter)
{
	newInertia.inverseMatrix();
	this->setInvertInertiaTensor(newInertia);
	this->setAngularDamping(newAngDamping);
}

void RigidBody::setMassCenter(Particle massCenterParticle) {
	this->massCenter = massCenterParticle;
};


Particle& RigidBody::getMassCenter() {
	return massCenter;
};

Particle const& RigidBody::getMassCenter() const {
	return massCenter;
};

void RigidBody::setOrientation(Quaternion objectOrientation) {
	this->orientation = objectOrientation;
};

Quaternion RigidBody::getOrientation() const {
	return orientation;
};

void RigidBody::setRotation(Vector3 objectRotation) {
	this->rotation = objectRotation;
};

Vector3 RigidBody::getRotation() const {
	return rotation;
};

void RigidBody::setTransformMatrix(Matrix4 matrixBodyToWorld) {
	this->transformMatrix = matrixBodyToWorld;
};

Matrix4 RigidBody::getTransformMatrix() const {
	return transformMatrix;
};

void RigidBody::setInvertInertiaTensor(Matrix3 invertInertia) {
	this->invertInertiaTensor = invertInertia;
};

Matrix3 RigidBody::getInvertInertiaTensor() const {
	return invertInertiaTensor;
};

void RigidBody::setAngularDamping(float angularDampingCoeff) {
	this->angularDamping = angularDampingCoeff;
};

float RigidBody::getAngularDamping() const {
	return angularDamping;
};

void RigidBody::calculateDerivedDatas() {
	// Collect the data in the quaternion
	double w = this->orientation.getW();
	double x = this->orientation.getX();
	double y = this->orientation.getY();
	double z = this->orientation.getZ();
	// Create the new data for the orientation matrix
	double a = 1 - 2 * (y * y + z * z);
	double b = 2 * (x * y + z * w);
	double c = 2 * (x * y - y * w);
	double d = 2 * (x * y - z * w);
	double e = 1 - 2 * (x * x + z * z);
	double f = 2 * (y * z + x * w);
	double g = 2 * (x * z + y * w);
	double h = 2 * (y * z - x * w);
	double i = 1 - 2 * (x * x + y * y);
	Matrix3 M = Matrix3(a, b, c, d, e, f, g, h, i);
	// Collect the position of the mass center
	Vector3 position = massCenter.getPosition();
	// Create the matrix bodyspace to worldspace
	Matrix4 transform = Matrix4(M, position);
	this->setTransformMatrix(transform);


}

void RigidBody::addForceAtPoint(Vector3 force, Vector3 point) {
	Vector3 massCenterPosition = massCenter.getPosition();
	Vector3 pointCOM = massCenterPosition - point;
	massCenter.accumulationOfForces += force;
	accumulationOfTorques = accumulationOfTorques + point.vectorialProduct(force);
}

void RigidBody::addForceAtBodyPoint(Vector3 force, Vector3 point) {
	Vector3 pointWorld = transformMatrix.getMatrix3() * point;
	this->addForceAtPoint(force, pointWorld);
}

void RigidBody::clearAccumulators() {
	massCenter.resetAccumulationForces();
	accumulationOfTorques = Vector3(0, 0, 0);
}

void RigidBody::integrate(float time) {
	// Integrate mass center (linear acceleration/velocity).
	massCenter.integrate(time);
	
	// Update orientation

	// Calculate the transform matrix
	calculateDerivedDatas();
	// Clear the accumulators of forces and torques
	clearAccumulators();
}