#pragma once
#include "../Vector.hpp"
#include "Matrix3.hpp"

using namespace std;

class Quaternion
{
    private:
        float w; //real part
        float x; //first imaginary number
        float y; //second imaginary number
        float z; //third imaginary number
    public:
        //Constructors :
        Quaternion();
        Quaternion(float w, float x, float y, float z);
        Quaternion(float w, Vector3 imaginaryNumbers);

        //Getters  :
        float getW() const; //scalar
        float getX() const; //first imaginary number
        float getY() const; //second imaginary number
        float getZ() const; //third imaginary number
        Vector3 getImaginaryNumbers(); //all imaginary numbers:
            
        //Setters
        void setRealNumber(float w);
        void setImaginaryNumbers(Vector3 imaginaryNumbers);
        void setImaginaryNumbers(float x, float y, float z);

        //Inverse and conjugate
        Quaternion getConjugate();
        Quaternion getInverse();
        float getNorm();

        //Normalise le quaternion
        void normalize();


        //Transform the quaternion into a matrix
        Matrix3 quaternionIntoMatrix();
        
        //Overload of operators :
        Quaternion operator+(Quaternion other); // Addition
        Quaternion operator-(Quaternion other); //Soustraction
        Quaternion operator*(Quaternion other); //Multiplication
        Quaternion operator*(const float k); //Multiplication
        // Quaternion operator^(int); //Exponentiation

};

//Overload ostream operator
ostream& operator<<(ostream& os, const Quaternion& q);

//Overload *
Quaternion operator*(const float k, Quaternion q);
Quaternion operator*(Quaternion q, const float k);