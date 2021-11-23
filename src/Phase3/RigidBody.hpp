#pragma once

#include "../Particle.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

class RigidBody
{
private:
    Particle massCenter;
    /// Orientation of the object.
    Quaternion orientation;
    /// Rotation of the object ie angular velocity.
    Vector3 rotation;
    /// To do the conversion BodySpace to WorldSpace
    Matrix4 transformMatrix;
    /// Inertia momentum of the object
    Matrix3 invertInertiaTensor;
    /// Amount of angular velocity kept at each frame, simulating the friction.
    float angularDamping;
public:
    /// Constructor
    RigidBody(Particle,Matrix3,float);
    /// Setters and getters of the private attributes
    void setMassCenter(Particle);
    Particle& getMassCenter();
    Particle const& getMassCenter() const;
    void setOrientation(Quaternion);
    Quaternion getOrientation() const;
    void setRotation(Vector3);
    Vector3 getRotation() const;
    void setTransformMatrix(Matrix4);
    Matrix4 getTransformMatrix() const;
    void setInvertInertiaTensor(Matrix3);
    Matrix3 getInvertInertiaTensor() const;
    void setAngularDamping(float);
    float getAngularDamping() const;
    /// Method to calculate the transformMatrix
    void calculateDerivedDatas();
    /// Accumulator of forces for the current frame
    Vector3 accumulationOfForces;
    /// Accumulator of torques for the current frame
    Vector3 accumulationOfTorques;
    /// To apply some force to some point
    void addForceAtPoint(Vector3, Vector3);
    /// To apply some force to some point depending on the object position
    void addForceAtBodyPoint(Vector3, Vector3);
    // To clear the accumulators before working on the next frame
    void clearAccumulators();
    /// Integrate the state of the RigidBody
    void integrate(float time);
};