#include "World.hpp"
#include "Phase2/ParticleForceGenerator.hpp"
#include "Phase2/GravityGenerator.hpp"

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
    }
    // Clean all particles.
    for(auto* p : particleList) {
        p->resetAccumulationForces();
    }
}


void World::resolveContacts(std::vector<ParticleContact> contacts) {
    if(contacts.size() > 0){
        int iteration = contacts.size()*2;
        int usedIteration = 0;
        while(usedIteration <= iteration){
            float vs = 0;
            int idx = -1;
            for(int i = 0; i < contacts.size(); i++){
                float newVs = contacts[i].vsCalculation();
                if(newVs < vs){
                    idx = i;
                    vs = newVs;
                }
            }
            if(idx >= 0){
                contacts[idx].resolve(deltaTime);
                contacts.erase(contacts.begin() + idx);
            }
            usedIteration++;
        }   
    }
}


//Overload of << 
ostream& operator<<(ostream& os, const World& I){
    os << "======== Integrator ========\n" << "Framerate : " << I.getFrameRate() << "\nGravity : " << I.gravity << "\nList of Particles : \n" <<  endl;
    for(auto* p : I.particleList){
        os << *p << endl;
    }
    return os;
}