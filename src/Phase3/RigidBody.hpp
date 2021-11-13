#pragma once

#include "../Particle.hpp"

class RigidBody
{
private:
    Particle massCenter;
    /// 1 / mass of the particle, 0 for infinite mass = static object.  
    float inverseMass;
    /// Damping used for this particle: amount of velocity kept at each frame, simulating the friction.
    float damping;
    /// Position of the particle.
    Vector3 position;
    /// Velocity of the particle.
    Vector3 velocity;
    /// Orientation of the particle.
    Quaternion orientation;
    /// Rotation of the particle.
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
    void setInverseMass(float);
    float getInverseMass();
    void setDamping(float);
    float getDamping();
    void setPosition(Vector3);
    Vector3 getPosition();
    void setVelocity(Vector3);
    Vector3 getVelocity();
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