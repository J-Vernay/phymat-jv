#pragma once

#include "RigidBody.hpp"
#include <vector>

class Star : public RigidBody {
public:
    Star(RigidBody const& rigidbody) : RigidBody(rigidbody) {}

    /// Draw the star at its position with its orientation.
    void draw();
};
