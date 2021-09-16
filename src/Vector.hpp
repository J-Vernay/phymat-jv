#pragma once
#include <iostream>
using namespace std;

//TO DO : add exceptions
// - add norm?
// - overload operators for scalar and vectorial product

class Vector3 {
    public:
        

        //Constructors
        Vector3();
        Vector3(float, float, float);

        //getters
        float getx();
        float gety();
        float getz();

        //Operator overload
        Vector3 operator+(const Vector3);
        Vector3 operator-(const Vector3);
        Vector3 operator*(const float);
        Vector3 operator/(const float);
        friend ostream& operator<<(ostream& os, const Vector3&);

        //Check if well placed
        Vector3 vectorialProduct(Vector3);
        float scalarProduct(Vector3);
        //float norm();
        //void normalise();

    private:
        float x;
        float y;
        float z;
};

//Conctructors
Vector3::Vector3(){
    this->x = 1;
    this->y = 1;
    this->z = 1;
}

Vector3::Vector3(float a, float b, float c){
    this->x = a;
    this->y = b;
    this->z = c;
}

//Getters
float Vector3::getx(){
    return x;
}

float Vector3::gety(){
    return y;
}

float Vector3::getz(){
    return z;
}


//Operator overload
Vector3 Vector3::operator+(const Vector3 v){
    Vector3 V = Vector3(this->x+v.x,this->y+v.y,this->z+v.z);
    return V;
}

Vector3 Vector3::operator-(const Vector3 v){
    Vector3 V = Vector3(this->x-v.x,this->y-v.y,this->z-v.z);
    return V;
}

Vector3 Vector3::operator*(const float k){
    Vector3 V = Vector3(this->x*k,this->y*k,this->z*k);
    return V;
}

Vector3 operator*(const double k, Vector3 V1){
    Vector3 V2 = Vector3(V1.getx()*k,V1.gety()*k,V1.getz()*k);
    return V2;
}

Vector3 Vector3::operator/(const float k){
    Vector3 V = Vector3(this->x/k,this->y/k,this->z/k);
    return V;
}

Vector3 operator/(const double k, Vector3 V1){
    Vector3 V2 = Vector3(k/V1.getx(),k/V1.gety(),k/V1.getz());
    return V2;
}

ostream& operator<<(ostream& os, const Vector3& V){
    os << "x : " << V.x << "\n" << "y : " << V.y << "\n" << "z : " << V.z << "\n";
    return os;
}


//Useful Methods
Vector3 Vector3::vectorialProduct(Vector3 V){
    return Vector3(y*V.getz()-z*V.gety(), z*V.getx()-x*V.getz(), x*V.gety()-y*V.getx());
}

float Vector3::scalarProduct(Vector3 V){
    return x*V.getx() + y*V.gety() + z*V.getz();
}
