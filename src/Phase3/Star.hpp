#pragma once

#include "RigidBody.hpp"
#include <vector>

class Star : public RigidBody {
public:
    Star(Particle const& mass_center, Matrix3 inertia, float angdamping) : RigidBody(mass_center, inertia, angdamping) {}
    ~Star() override {}

    BoundingBox getBoundingBox() const override;

    /// Draw the star at its position with its orientation.
    void draw() const;
};
