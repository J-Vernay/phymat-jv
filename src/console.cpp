#include <ostream>
#include <iostream>
#include <unistd.h>
#include "Vector.hpp"
#include "Particle.hpp"
#include "Integrator.hpp"
 
 
using namespace std;

//This script plot the (x, z) position of a particule 
// initial position : (1, 1, 1)
// initial velocity : (0, 0, 0)
// initial acceleration : (1, 1, 60)
// mass : 1
// damping : 0
// type of projectile : 0
// => all of these parameters can be changed in the main function below

// To launch this script : g++ console.cpp Vector.cpp Particle.cpp Integrator.cpp

//Note : The coordinates system is upside-down :
 
/*
 ______________> x
|
|
|
|
\/
z
 
*/
 
//generate nb space charater
string genSpace(int nb) {
    string space = "";
    for (int i = 0; i < nb; i++){
        space += " ";
    }
    return space;
}
 
//generate nb \n charater
string genlinereturn(int nb){
    string space = "";
    for (int i = 0; i < nb; i++){
        space += "\n";
    }
    return space;
}
 
//display a particle at (x,z) in the consol
void displayAt(int x, int z){
    cout << genlinereturn(z) << genSpace(x) << "O" << endl;
 
} 
 
int main(){
    //Creation of a paricle
    float mass = 1;
    Vector3 p = Vector3(1,1,1);
    Vector3 a = Vector3(1,1,60);
    Vector3 v = Vector3(0,0,0);
    //Vector3 o = Vector3(0.f,1.f,1.f);
 
    Particle P = Particle(1.0f,p,v,a,0,0);
    cout << P << endl;
    //end creation
 
    //Integrator 
    Integrator I = Integrator();
 
    I.addParticle(P);
    cout << I.getParticleList().size() << endl;
 
    displayAt(P.getPosition().getx(), P.getPosition().getz());
    //End init
 
 
    while (I.getParticleList().size() >= 1){ //~update while the z position of the particle is abiove 0

        printf("\033c"); //clear consol
        
        //cout << "oui" << endl;
        I.updateAll(); // update 
        for (auto &p : I.getParticleList()){
            //cout << p << endl;
            // display coordinates
            cout << p.getPosition().getx() << " : " << p.getPosition().gety() << " : " << p.getPosition().getz() << endl;
            //display particle at the right place in console
            displayAt(p.getPosition().getx()*10, p.getPosition().getz()/10);
        }
        sleep(0.8); //wait 
    }
 
    return 0;
 
 
}