#include "ParticleContactResolver.hpp"


ParticleContactResolver::ParticleContactResolver(/* args */)
{
}

ParticleContactResolver::~ParticleContactResolver()
{
}

//Resolve all contacts
void ParticleContactResolver::resolveContact(vector<ParticleContact> contacts, float frameDuration){
    if(contacts.size()>0){
        iteration = contacts.size()*2;
        usedIteration = 0;
        while(usedIteration<=iteration){
            float vs = 0;
            int idx = -1;
            for(int i = 0; i<contacts.size(); i++){
                float newVs = contacts[i].vsCalculation();
                if(newVs < vs){
                    idx = i;
                    vs = newVs;
                }
            }
            if(idx >= 0){
                contacts[idx].resolve(frameDuration);
            }
            usedIteration++;
        }   
    }
    
}

void ParticleContactResolver::setIteration(int i){
    iteration = i;
}