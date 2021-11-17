#pragma once
#include <iostream>
#include <math.h>
#include "ExceptionForVector.hpp"
#include "Phase3/Matrix3.hpp"
#include "Phase3/Matrix4.hpp"

using namespace std;

/// Class representing a 3D vector with utility methods and operator overloading.
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
        Vector3 operator-() const;
        Vector3 operator+(const Vector3);
        Vector3& operator+=(const Vector3);
        Vector3 operator-(const Vector3);
        Vector3 operator*(const float);
        Vector3 operator/(const float);
        Vector3 operator^(Vector3);
        friend ostream& operator<<(ostream& os, const Vector3&);

        //Check if well placed
        Vector3 vectorialProduct(Vector3) const;
        float scalarProduct(Vector3) const;
        float norm() const;

        float squareNorm() const { return scalarProduct(*this); }

    private:
        float x;
        float y;
        float z;
};

float scalarProduct(Vector3, Vector3);

Vector3 vectorialProduct(Vector3, Vector3);

float norm(Vector3);

Vector3 operator*(const double k, Vector3 v1);

float operator*(Vector3 k, Vector3 v1);