#include "World.hpp"
#include "Phase2/ParticleForceGenerator.hpp"
#include "Phase2/GravityGenerator.hpp"
#include "Phase4/Octree.hpp"

//Constructor
//Default : gravity = 10, particleList empty, frameRate = 60 fps
World::World() {
    gravity = Vector3(0,0,-10);
    deltaTime = 1/60.f;
}

//Setters
void World::setGravity(Vector3 newGravity){
    gravity = newGravity;
}

void World::setFrameRate(double newFrameRate){
    if(newFrameRate > 0){
        deltaTime = 1/newFrameRate;
    }
    else {
        throw ExceptionNegativOrNullFramerate();
    }

}

void World::integrate() {
    // Apply all registed forces to their respective particles.
    for(ParticleForceGenerator* force : registerOfForces) {
        force->updateForces(deltaTime); 
    }
    // Update acceleration, velocity and position according to accumulated forces.
    for (auto* p : particleList) {
        // Include gravity now for all particles with finite mass.
        if (p->getInverseMass() != 0)
            GravityGenerator(p).updateForces(deltaTime);
        p->integrate(deltaTime);
        // Clear accumulation.
        p->resetAccumulationForces();
    }
    // Do the same for rigid bodies.
    for (auto* rb : rigidbodyList) {
        // Include gravity now for all particles with finite mass.
        auto& p = rb->getMassCenter();
        if (p.getInverseMass() != 0)
            GravityGenerator(&p).updateForces(deltaTime);
        rb->integrate(deltaTime);
        // Clear accumulation.
        rb->clearAccumulators();
    }
    /// Constructs an octree.
    Octree octree{rigidbodyList};
    generateContacts(octree.getPotentialCollisions());
}

//Resolve all contacts in a contact list
void World::resolveContacts(std::vector<ParticleContact> contacts) {
    if(contacts.size() > 0){
        //iteration goes up to 2 * init number of iteration, then, contacts are considered resolved
        int iteration = contacts.size()*2;
        int usedIteration = 0;
        while(usedIteration <= iteration){
            float vs = 0;
            int idx = -1;
            for(int i = 0; i < contacts.size(); i++){
                float newVs = contacts[i].vsCalculation();
                //the first contact resolved is the one that particles get close the fastest
                //finds the first contact to resolve and store its ID
                if(newVs < vs){
                    idx = i;
                    vs = newVs;
                }
            }
            //if there is a contact to resolve, then resolve it
            if(idx >= 0){
                contacts[idx].resolve(deltaTime);
                contacts.erase(contacts.begin() + idx);
            }
            usedIteration++;
        }   
    }
}

// Generate the contacts from potential contact from the broading phase :
std::vector<Contact> World::generateContacts(std::vector<PotentialCollision> potentialCollisions){    
    std::vector<Contact> contact_list;
    
    //Go through every potential collision
    //WHere a potential collision is a pair of rigidBody
    for(auto& potentialCollision : potentialCollisions){
        Plane* planeA = dynamic_cast<Plane*>(potentialCollision.first); 
        Plane* planeB = dynamic_cast<Plane*>(potentialCollision.second);

        Plane* plane = nullptr;
        RigidBody* rigidBody = nullptr;
        if (planeA && !planeB) {
            rigidBody = potentialCollision.second;
            plane = planeA;
        } else if (planeB && !planeA) {
            rigidBody = potentialCollision.first;
            plane = planeB;
        } else {
            // Either two planes (nothing to do) or two rigidbodies (not implemented).
            // Do nothing.
            continue;
        }

        float distanceBetweenTheRigidBodies = 0.0f;

        cout << "Potential collision between plane and object!\n";

        for(auto point : rigidBody->getPoints()){//Go through all the points
            distanceBetweenTheRigidBodies = getDistanceFromTheWall(plane, point); //Test the distance between the wall and the rigidbody
            if(distanceBetweenTheRigidBodies > 0){ //If there is a contact => the absolute distance is the interpenetration
                //Add the contact to the contact list :
                Contact contact = Contact();
                contact.setContactNormal(plane->getNormale());  //the normal is the same than the plane
                contact.setContactPoint(point); //the point is the point tested
                contact.setPenetration(abs(distanceBetweenTheRigidBodies)); //Interpenetration is the absolute distance
                contact_list.push_back(contact); //Add the correct contact
                cout << contact << "\n";
                break;
            }
        }
    }
    return contact_list;
}

//Measure the distance between a point and a wall, 
//if the distance is positiv : there is no contact between the rigidBody and the plane,
//if the distance is negativ the is a contact and the distance is the interpenetration
float World::getDistanceFromTheWall(Plane * plane, Vector3 point){
    Vector3 normale = plane->getNormale();
    float offset = plane->getOffset();

    //n.p + d => distance between the plane and the rigidBody
    return normale*point - offset;
}


//Overload of << 
ostream& operator<<(ostream& os, const World& I){
    os << "======== Integrator ========\n" << "Framerate : " << I.getFrameRate() << "\nGravity : " << I.gravity << "\nList of Particles : \n" <<  endl;
    for(auto* p : I.particleList){
        os << *p << endl;
    }
    return os;
}