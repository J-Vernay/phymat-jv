#include "Vector.hpp"

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
    //Vector3 v = 
    return Vector3(this->x+v.x,this->y+v.y,this->z+v.z);
}

Vector3 Vector3::operator-(const Vector3 v){
    return Vector3(this->x-v.x,this->y-v.y,this->z-v.z);  
}

Vector3 Vector3::operator*(const float k){
    return Vector3(this->x*k,this->y*k,this->z*k);
}

//scalar product
float Vector3::operator*(Vector3 v){
    return x*v.getx() + y*v.gety() + z*v.getz();
}

Vector3 operator*(const double k, Vector3 v1){
    return Vector3(v1.getx()*k,v1.gety()*k,v1.getz()*k);
}

float operator*(Vector3 v1, Vector3 v2){
    return scalarProduct(v1,v2);
}

Vector3 Vector3::operator/(const float k){
    if(k == 0){
        throw ExceptionDivideByNullScalar;
    }
    else {
        return Vector3(this->x/k,this->y/k,this->z/k);
    }
}

Vector3 Vector3::operator^(Vector3 v){
    return Vector3(y*v.getz()-z*v.gety(), z*v.getx()-x*v.getz(), x*v.gety()-y*v.getx());
}

Vector3 operator^(Vector3 v1,Vector3 v2){
    return vectorialProduct(v1,v2);
}

Vector3 operator/(const double k, Vector3 v1){
    if(v1.getx() == 0 || v1.gety() == 0 || v1.getz() == 0){
        throw ExceptionDivideByNullComponent;
    }
    return Vector3(k/v1.getx(),k/v1.gety(),k/v1.getz());
}

ostream& operator<<(ostream& os, const Vector3& v){
    os << "x : " << v.x << "\n" << "y : " << v.y << "\n" << "z : " << v.z << "\n";
    return os;
}


//Useful Methods
Vector3 Vector3::vectorialProduct(Vector3 v){
    return Vector3(y*v.getz()-z*v.gety(), z*v.getx()-x*v.getz(), x*v.gety()-y*v.getx());
}

float Vector3::scalarProduct(Vector3 v){
    return x*v.getx() + y*v.gety() + z*v.getz();
}

float Vector3::norm(){
    return pow(pow(x,2)+pow(y,2)+pow(z,2),0.5);
}

//Other useful methods

float scalarProduct(Vector3 v1, Vector3 v2){
    return v1.getx()*v2.getx() + v1.gety()*v2.gety() + v1.getz()*v2.getz();
}

Vector3 vectorialProduct(Vector3 v1, Vector3 v2){
    return Vector3(v1.gety()*v2.getz()-v1.getz()*v2.gety(), v1.getz()*v2.getx()-v1.getx()*v2.getz(), v1.getx()*v2.gety()-v1.gety()*v2.getx());
}

float norm(Vector3 v){
    return pow(pow(v.getx(),2)+pow(v.gety(),2)+pow(v.getz(),2),0.5);
}