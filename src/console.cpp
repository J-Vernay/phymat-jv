#include <ostream>
#include <iostream>
#include <unistd.h>
#include "Vector.hpp"
#include "Particle.hpp"
#include "Integrator.hpp"
 
 
using namespace std;
 
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
 
//display a particle at (x,y) in the consol
void displayAt(int x, int y){
    cout << genlinereturn(y) << genSpace(x) << "O" << endl;
 
}
 
/*
 ______________> x
|
|
|
|
y
 
*/
 
 
int main(){
    //Creation of a paricle
    float mass = 1;
    Vector3 p = Vector3(1,1,1);
    Vector3 a = Vector3(1,1,1000);
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
 
 
    while (true){ //~update

        printf("\033c"); //clear consol
        if(I.getParticleAt(0).getPosition().getz() < 0){ //if particle cross z = 0
            cout << "crossed z = 0" << endl;
            break;
        }
        //cout << "oui" << endl;
        I.updateAll(); // update (note : comment clearAll in integrator:updateAll !!!)
        for (auto &p : I.getParticleList()){
            //cout << p << endl;
            // display coordinates
            cout << p.getPosition().getx() << " : " << p.getPosition().gety() << " : " << p.getPosition().getz() << endl;
            //display particle at the right place in consol
            displayAt(p.getPosition().getx()*10, p.getPosition().getz()/100);
        }
        sleep(0.8); //wait 
    }
 
    // cout << "Update Acceleration :\n " << I.getParticleList()[0].getAcceleration() << endl;
    // cout << "Update Position : \n" << I.getParticleList()[0].getPosition() << endl;
    // cout << "Update Velocity : \n" << I.getParticleAt(0).getVelocity() << endl;
 
    return 0;
 
 
}