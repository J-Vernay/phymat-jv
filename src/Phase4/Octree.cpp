#include "Octree.hpp"
#include "../Phase3/RigidBody.hpp"

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

Octree::Octree(std::vector<RigidBody*> rigid_bodies) {
    float xmin, xmax, ymin, ymax, zmin, zmax;
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
    return collisions;
}

void Octree::Node::insertChild(BoundingBox const &child_bbox, RigidBody *child_ptr) {
    if (auto* bodies_ptr = std::get_if<ChildBodies>(&children)) {
        if (bodies_ptr->size() < SubdivisionThreshold) {
            bodies_ptr->push_back(child_ptr);
            return;
        }
        // We need to split the node into 8 children nodes.
        ChildBodies bodies = std::move(*bodies_ptr);
        children = ChildNodes{
            { bbox.subdivision(-1, -1, -1) },
            { bbox.subdivision(-1, -1,  1) },
            { bbox.subdivision(-1,  1, -1) },
            { bbox.subdivision(-1,  1,  1) },
            { bbox.subdivision( 1, -1, -1) },
            { bbox.subdivision( 1, -1,  1) },
            { bbox.subdivision( 1,  1, -1) },
            { bbox.subdivision( 1,  1,  1) },
        };
        ChildNodes& nodes = std::get<ChildNodes>(children);

        for (RigidBody* child : bodies) {
            BoundingBox child_bbox = child->getBoundingBox();
            for (Node& node : nodes)
                if (child_bbox.overlapsWith(node.bbox))
                    node.insertChild(child_bbox, child);
        }
    }

    ChildNodes& nodes = std::get<ChildNodes>(children);
    for (Node& node : nodes)
        if (child_bbox.overlapsWith(node.bbox))
            node.insertChild(child_bbox, child_ptr);
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