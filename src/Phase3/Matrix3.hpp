#pragma once
#include "../Vector.hpp"

using namespace std;


class Matrix3
{
private:
    float elements[9];

public:
    Matrix3();
    Matrix3(float[]);
    Matrix3(float,float,float,float,float,float,float,float,float);
    void setElement(float, int);
    float getElement(int);

    float det();
    
    void transposeMatrix();
    Matrix3 getTransposeMatrix();

    void inverseMatrix();
    Matrix3 getInverseMatrix();

    Matrix3 operator+(Matrix3);
    Matrix3 operator-(Matrix3);
    Matrix3 operator*(Matrix3);
    Vector3 operator*(Vector3);
};

