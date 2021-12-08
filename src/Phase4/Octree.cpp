#include "Octree.hpp"
#include "../Phase3/RigidBody.hpp"


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

}

void Octree::Node::findPotentialCollisions(std::vector<PotentialCollision> &collisions) const {
    if (auto* nodes = std::get_if<ChildNodes>(&this->children)) {
        for (auto& node : *nodes)
            node.findPotentialCollisions(collisions);
    } else if (auto* bodies = std::get_if<ChildBodies>(&this->children)) {
        
    } else {
        // Node in error state, do nothing
    }
}