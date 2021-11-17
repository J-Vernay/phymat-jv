#pragma once

#include "../Particle.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"

class RigidBody
{
private:
    Particle massCenter;
    /// Orientation of the object.
    Quaternion orientation;
    /// Rotation of the object.
    Vector3 rotation;
    /// To do the conversion BodySpace to WorldSpace
    Vector3 transformMatrix;
    /// Inertia momentum of the object
    Matrix3 invertInertiaTensor;
    /// Amount of angular velocity kept at each frame, simulating the friction.
    float angularDamping;
public:
    RigidBody();
    /// Setters and getters of the private attributes
    void setMassCenter(Particle);
    Particle getMassCenter();
    void setOrientation(Quaternion);
    Quaternion getOrientation();
    void setRotation(Vector3);
    Vector3 getRotation();
    void setTransformMatrix(Vector3);
    Vector3 getTransformMatrix();
    void setInvertInertiaTensor(Matrix3);
    Matrix3 getInvertInertiaTensor();
    void setAngularDamping(float);
    float getAngularDamping();
    /// Method to calculate the transformMatrix
    void calculateDerivedDatas();
    /// To apply some force to some point
    void addForceAtPoint(Vector3, Vector3);
    /// To apply some force to some point depending on the object position
    void addForceAtBodyPoint(Vector3, Vector3);
};