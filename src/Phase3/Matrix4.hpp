#pragma once

#include "Matrix3.hpp"
#include "../Vector.hpp"


using namespace std;

class Matrix4
{
private:
/**  Matrix3     Vector3
 * [a] [b] [c] [x]
 * [d] [e] [f] [y]
 * [g] [h] [i] [z]
 * [0] [0] [0] [1]  added ligne (not stored in this class)
 */
    float elements[12];
public:
    Matrix4();
    Matrix4(float[]);
    Matrix4(float,float,float,float,float,float,float,float,float,float,float,float);
    Matrix4(Matrix3, Vector3) ;
    
    void setElement(float, int);
    float getElement(int);

    Matrix4 operator+(Matrix4);
    Matrix4 operator-(Matrix4);
    Matrix4 operator*(Matrix4);
    //Vector3 operator*(Vector3);

    Matrix3 getMatrix3();
    Vector3 getVector3();

    Vector3 applyOnPt(Vector3);
    Vector3 applyOnVec(Vector3);

};

Vector3 applyMatrixOnPt(Matrix4,Vector3);
Vector3 applyMatrixOnVec(Matrix4,Vector3);


