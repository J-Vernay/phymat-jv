#pragma once

#include "../Vector.hpp"

/// Forward declaration to use pointers to rigid bodies.
class RigidBody;

#include <variant>
#include <vector>

using PotentialCollision = std::pair<RigidBody *, RigidBody *>;

struct BoundingBox {
  Vector3 pos;
  Vector3 half_size;
  bool overlapsWith(BoundingBox const &other) const;
  BoundingBox subdivision(int x, int y, int z) const;
};

class Octree {
  static constexpr int SubdivisionThreshold = 2;

public:
  /// Builds an octree with the given rigid bodies.
  Octree(std::vector<RigidBody *> rigid_bodies);
  /// Returns all potential collisions found in the octree.
  std::vector<PotentialCollision> getPotentialCollisions() const;

private:
  struct Node {
    /// A node has a bounding box, which intersects with the bounding boxes of
    /// all its children.
    BoundingBox bbox;
    /// A node is referring either to its child nodes, or to the rigid bodies it
    /// include.
    using ChildBodies = std::vector<RigidBody*>;
    using ChildNodes = std::vector<Node>;
    std::variant<ChildBodies, ChildNodes> children;

    /// Adds a child to the node, eventually splitting the stored rigidbodies in
    /// sub-nodes.
    void insertChild(BoundingBox const &child_bbox, RigidBody *child_ptr);
    /// Retrieves potential collisions, when bounding boxes intersect.
    void findPotentialCollisions(std::vector<PotentialCollision> &collisions) const;
  };

  Node root;
};
