#pragma once

#include <vector>

using namespace std;

class Quaternion
{
private:
    double realNum;
    vector<double> imaginaryNums;
    
public:
    Quaternion(/* args */);
    ~Quaternion();

    double getRealNum();
    vector<double> getImaginaryNums();
    
    void setRealNum(double);
    void setImaginaryNums(vector<double>);

    //negation
    //norme
    //conjugate
    //inverse
    //multiplication
    //division?
    //exponantiation
};
