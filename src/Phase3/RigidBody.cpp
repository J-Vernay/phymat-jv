#include "RigidBody.hpp"

RigidBody::RigidBody(){

}

void RigidBody::setMassCenter(Particle massCenterParticle) {
	this->massCenter = massCenterParticle;
};

Particle RigidBody::getMassCenter() {
	return massCenter;
};

void RigidBody::setInverseMass(float mass) {
	this->inverseMass = mass;
};

float RigidBody::getInverseMass() {
	return inverseMass;
};

void RigidBody::setDamping(float dampingCoeff) {
	this->damping = dampingCoeff;
};

float RigidBody::getDamping() {
	return damping;
};

void RigidBody::setPosition(Vector3 objectPosition) {
	this->position = objectPosition;
};

Vector3 RigidBody::getPosition() {
	return position;
};

void RigidBody::setVelocity(Vector3 objectVelocity) {
	this->velocity = objectVelocity;
};

Vector3 RigidBody::getVelocity() {
	return velocity;
};

void RigidBody::setOrientation(Quaternion objectOrientation) {
	this->orientation = objectOrientation;
};

Quaternion RigidBody::getOrientation() {
	return orientation;
};

void RigidBody::setRotation(Vector3 objectRotation) {
	this->rotation = objectRotation;
};

Vector3 RigidBody::getRotation() {
	return rotation;
};

void RigidBody::setTransformMatrix(Vector3 matrixBodyToWorld) {
	this->transformMatrix = matrixBodyToWorld;
};

Vector3 RigidBody::getTransformMatrix() {
	return transformMatrix;
};

void RigidBody::setInvertInertiaTensor(Matrix3 invertInertia) {
	this->invertInertiaTensor = invertInertia;
};

Matrix3 RigidBody::getInvertInertiaTensor() {
	return invertInertiaTensor;
};

void RigidBody::setAngularDamping(float angularDampingCoeff) {
	this->angularDamping = angularDampingCoeff;
};

float RigidBody::getAngularDamping() {
	return angularDamping;
};