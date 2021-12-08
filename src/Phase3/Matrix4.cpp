#include "Matrix4.hpp"



Matrix4::Matrix4(){
    for (int i = 0; i < std::size(elements); i++)
    {
        elements[i]= 0;
    }
}

Matrix4::Matrix4(float newMatrix[]){
    for (int i = 0; i < std::size(elements); i++)
    {
        elements[i]= newMatrix[i];
    }
}

Matrix4::Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    elements[0] = a;
    elements[1] = b;
    elements[2] = c;
    elements[3] = d;
    elements[4] = e;
    elements[5] = f;
    elements[6] = g;
    elements[7] = h;
    elements[8] = i;
    elements[9] = j;
    elements[10] = k;
    elements[11] = l;
}

Matrix4::Matrix4(Matrix3 mtx, Vector3 vct){
    elements[0] = mtx.getElement(0);
    elements[1] = mtx.getElement(1);
    elements[2] = mtx.getElement(2);
    elements[3] = vct.getx();
    elements[4] = mtx.getElement(3);
    elements[5] = mtx.getElement(4);
    elements[6] = mtx.getElement(5);
    elements[7] = vct.gety();
    elements[8] = mtx.getElement(6);
    elements[9] = mtx.getElement(7);
    elements[10] = mtx.getElement(8);
    elements[11] = vct.getz();
}
    
void Matrix4::setElement(float value, int idx){
    if(idx > 11 || idx < 0){
        cout << "indice incorrect" << endl;
    }
    else{
        elements[idx] = value;
    }
}

float Matrix4::getElement(int idx){
    if(idx > 11 || idx < 0){
        cout << "indice incorrect" << endl;
        return NULL;
    }
    else{
        return elements[idx];
    }
}

Matrix4 Matrix4::operator+(Matrix4 mtx){
    Matrix4 newMtx;
    for (int i = 0; i < std::size(elements); i++)
    {
        newMtx.setElement(elements[i]+mtx.getElement(i), i);
    }
    return newMtx;
}

Matrix4 Matrix4::operator-(Matrix4 mtx){
    Matrix4 newMtx;
    for (int i = 0; i < std::size(elements); i++)
    {
        newMtx.setElement(elements[i]-mtx.getElement(i), i);
    }
    return newMtx;
}

//Matrix4 Matrix4::operator*(Matrix4 mtx){}

//Matrix4::Vector3 operator*(Vector3){}

Matrix3 Matrix4::getMatrix3(){
    Matrix3 mtx;
    mtx.setElement(elements[0],0);
    mtx.setElement(elements[1],1);
    mtx.setElement(elements[2],2);
    mtx.setElement(elements[4],3);
    mtx.setElement(elements[5],4);
    mtx.setElement(elements[6],5);
    mtx.setElement(elements[8],6);
    mtx.setElement(elements[9],7);
    mtx.setElement(elements[10],8);
    return mtx;
}

Vector3 Matrix4::getVector3(){
    Vector3 vct(elements[3],elements[7],elements[11]);
    return vct;
}

//Multiplication with Vec3 as Vec4. Last element set to 1
Vector3 Matrix4::applyOnPt(Vector3 vec){
    float x = elements[0]*vec.getx()+elements[1]*vec.gety()+elements[2]*vec.getz()+elements[3];
    float y = elements[4]*vec.getx()+elements[5]*vec.gety()+elements[6]*vec.getz()+elements[7];
    float z = elements[8]*vec.getx()+elements[9]*vec.gety()+elements[10]*vec.getz()+elements[11];
    Vector3 newVec(x,y,z);
    return newVec;
}

Vector3 applyMatrixOnPt(Matrix4 mtx,Vector3 vec){
    float x = mtx.getElement(0)*vec.getx()+mtx.getElement(1)*vec.gety()+mtx.getElement(2)*vec.getz()+mtx.getElement(3);
    float y = mtx.getElement(4)*vec.getx()+mtx.getElement(5)*vec.gety()+mtx.getElement(6)*vec.getz()+mtx.getElement(7);
    float z = mtx.getElement(8)*vec.getx()+mtx.getElement(9)*vec.gety()+mtx.getElement(10)*vec.getz()+mtx.getElement(11);
    Vector3 newVec(x,y,z);
    return newVec;
}

//Multiplication with Vec3 as Vec4. Last element set to 0
Vector3 Matrix4::applyOnVec(Vector3 vec){
    float x = elements[0]*vec.getx()+elements[1]*vec.gety()+elements[2]*vec.getz();
    float y = elements[4]*vec.getx()+elements[5]*vec.gety()+elements[6]*vec.getz();
    float z = elements[8]*vec.getx()+elements[9]*vec.gety()+elements[10]*vec.getz();
    Vector3 newVec(x,y,z);
    return newVec;
}

Vector3 applyMatrixOnVec(Matrix4 mtx,Vector3 vec){
    float x = mtx.getElement(0)*vec.getx()+mtx.getElement(1)*vec.gety()+mtx.getElement(2)*vec.getz();
    float y = mtx.getElement(4)*vec.getx()+mtx.getElement(5)*vec.gety()+mtx.getElement(6)*vec.getz();
    float z = mtx.getElement(8)*vec.getx()+mtx.getElement(9)*vec.gety()+mtx.getElement(10)*vec.getz();
    Vector3 newVec(x,y,z);
    return newVec;
}

ostream& operator<<(ostream& os, Matrix4& mtx){
    for(int i = 0; i<3;i++){
        os << mtx.getElement(i*4+0) << " " << mtx.getElement(i*4+1) << " " << mtx.getElement(i*4+2) << " " << mtx.getElement(i*4+3) << endl;
    }
    return os;
}