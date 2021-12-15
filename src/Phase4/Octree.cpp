#include "Octree.hpp"
#include "../Phase3/RigidBody.hpp"
#include "Plane.hpp"
#include <algorithm>

bool BoundingBox::overlapsWith(BoundingBox const &other) const {
    Vector3 minA = pos - half_size, maxA = pos + half_size,
        minB = other.pos - other.half_size, maxB = other.pos + other.half_size;
    return !(maxA.getx() < minB.getx() || maxB.getx() < minA.getx()
        || maxA.gety() < minB.gety() || maxB.gety() < minA.gety()
        || maxA.getz() < minB.getz() || maxB.getz() < minA.getz());
}

BoundingBox BoundingBox::subdivision(int x, int y, int z) const {
    Vector3 newpos = {
        pos.getx() + x * half_size.getx() / 2,
        pos.gety() + y * half_size.gety() / 2,
        pos.getz() + z * half_size.getz() / 2
    };
    return BoundingBox{newpos, half_size / 2};
}

Octree::Octree(std::unordered_set<RigidBody*> rigid_bodies) {
    float xmin = +INFINITY, xmax = -INFINITY,
          ymin = +INFINITY, ymax = -INFINITY,
          zmin = +INFINITY, zmax = -INFINITY;
    for (RigidBody* body : rigid_bodies) {
        BoundingBox bbox = body->getBoundingBox();
        Vector3 minpos = bbox.pos - bbox.half_size;
        Vector3 maxpos = bbox.pos + bbox.half_size;
        xmin = std::min(xmin, minpos.getx());
        xmax = std::max(xmax, maxpos.getx());
        ymin = std::min(ymin, minpos.gety());
        ymax = std::max(ymax, maxpos.gety());
        zmin = std::min(zmin, minpos.getz());
        zmax = std::max(zmax, maxpos.getz());
    }
    Vector3 halfsize = Vector3{xmax-xmin,ymax-ymin,zmax-zmin}/2;
    Vector3 center = Vector3{xmin,ymin,zmin} + halfsize;

    root.bbox = {center, halfsize};
    for (RigidBody* body : rigid_bodies) {
        BoundingBox bbox = body->getBoundingBox();
        root.insertChild(bbox, body);
    }
}

std::vector<PotentialCollision> Octree::getPotentialCollisions() const {
    std::vector<PotentialCollision> collisions;
    root.findPotentialCollisions(collisions);
    /// Removing duplicates.
    std::sort(collisions.begin(), collisions.end());
    collisions.erase(std::unique(collisions.begin(), collisions.end()), collisions.end());
    return collisions;
}

void Octree::Node::insertChild(BoundingBox const &child_bbox, RigidBody *child_ptr, int recursion_count) {
    if (auto* bodies_ptr = std::get_if<ChildBodies>(&children)) {
        // The node is currently storing bodies. Have we enough space
        // for storing another body?
        if (bodies_ptr->size() < SubdivisionThreshold || recursion_count >= MaxRecursion) {
            // If yes, add it.
            bodies_ptr->push_back(child_ptr);
            return;
        } else {
            // Else, the current node needs to be split and will now store
            // multiple sub-nodes.
            // First, create the subdivisions, initialized with empty ChildBodies.
            ChildNodes subnodes = {
                { bbox.subdivision(-1, -1, -1) },
                { bbox.subdivision(-1, -1,  1) },
                { bbox.subdivision(-1,  1, -1) },
                { bbox.subdivision(-1,  1,  1) },
                { bbox.subdivision( 1, -1, -1) },
                { bbox.subdivision( 1, -1,  1) },
                { bbox.subdivision( 1,  1, -1) },
                { bbox.subdivision( 1,  1,  1) },
            };
            // Then, populate them with the current child bodies + the new child.
            for (Node& subnode : subnodes) {
                for (RigidBody* rb : *bodies_ptr) {
                    BoundingBox rb_bbox = rb->getBoundingBox();
                    if (subnode.bbox.overlapsWith(rb_bbox)) {
                        subnode.insertChild(rb_bbox, rb, 0);
                    }
                }
                if (subnode.bbox.overlapsWith(child_bbox))
                    subnode.insertChild(child_bbox, child_ptr, recursion_count+1);
            }
            // Finally, store the subnodes in the current node.
            children = std::move(subnodes);
        } 
    } else {
        // We already store subnodes, add the child to the subnodes.
        for (Node& subnode : std::get<ChildNodes>(children)) {
            if (subnode.bbox.overlapsWith(child_bbox))
                subnode.insertChild(child_bbox, child_ptr, recursion_count+1);
        }
    }
}

void Octree::Node::findPotentialCollisions(std::vector<PotentialCollision> &collisions) const {
    if (auto* nodes_ptr = std::get_if<ChildNodes>(&children)) {
        for (auto& node : *nodes_ptr)
            node.findPotentialCollisions(collisions);
    } else if (auto* bodies_ptr = std::get_if<ChildBodies>(&children)) {
        auto& bodies = *bodies_ptr;
        int nb_bodies = bodies.size();
        for (int i = 0; i < nb_bodies; ++i)
            for (int j = i+1; j < nb_bodies; ++j)
                if (bodies[i]->getBoundingBox().overlapsWith(bodies[j]->getBoundingBox()))
                    collisions.push_back({bodies[i], bodies[j]});
    } else {
        // Node in error state, do nothing
    }
}