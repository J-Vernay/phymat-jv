#include "Matrix3.hpp"

Matrix3::Matrix3()
{
    for (int i = 0; i < sizeof(elements); i++)
    {
        elements[i]= 0;
    }
    
}

Matrix3::Matrix3(float newMatrix[]){
    for (int i = 0; i < sizeof(elements); i++)
    {
        elements[i]= newMatrix[i];
    }
}

Matrix3::Matrix3(float a,float b,float c,float d,float e,float f,float g,float h,float i){
    elements[0] = a;
    elements[1] = b;
    elements[2] = c;
    elements[3] = d;
    elements[4] = e;
    elements[5] = f;
    elements[6] = g;
    elements[7] = h;
    elements[8] = i;
}

void Matrix3::setElement(float value, int idx){
    if(idx > 8 || idx < 0){
        cout << "indice incorrect" << endl;
    }
    else{
        elements[idx] = value;
    }
}

float Matrix3::getElement(int idx){
    if(idx > 8 || idx < 0){
        cout << "indice incorrect" << endl;
        return NULL;
    }
    else{
        return elements[idx];
    }
}

float Matrix3::det(){
    float a = elements[0]*(elements[4]*elements[8]-elements[7]*elements[5]);
    float b = elements[1]*(elements[3]*elements[8]-elements[6]*elements[5]);
    float c = elements[2]*(elements[3]*elements[7]-elements[6]*elements[4]);

    return a-b+c;
}

void Matrix3::transposeMatrix(){
    float tmp;

    tmp = elements[1];
    elements[1] = elements[3];
    elements[3] = tmp;

    tmp = elements[2];
    elements[2] = elements[6];
    elements[6] = tmp;
    
    tmp = elements[5];
    elements[5] = elements[7];
    elements[7] = tmp;
}

Matrix3 Matrix3::getTransposeMatrix(){
    Matrix3 transposed(elements);
    transposed.transposeMatrix();
    return transposed;
}

void Matrix3::inverseMatrix(){
    float determinant = det();
    if(determinant == 0){
        cout<<"matrice non inversible"<<endl;
    }
    else{
        Matrix3 transposed = getTransposeMatrix();
        elements[0] = (transposed.getElement(4)*transposed.getElement(8)-transposed.getElement(7)*transposed.getElement(5))/determinant;
        elements[1] = -(transposed.getElement(3)*transposed.getElement(8)-transposed.getElement(6)*transposed.getElement(5))/determinant;
        elements[2] = (transposed.getElement(3)*transposed.getElement(7)-transposed.getElement(6)*transposed.getElement(4))/determinant;
        elements[3] = -(transposed.getElement(1)*transposed.getElement(8)-transposed.getElement(7)*transposed.getElement(2))/determinant;
        elements[4] = (transposed.getElement(0)*transposed.getElement(8)-transposed.getElement(6)*transposed.getElement(2))/determinant;
        elements[5] = -(transposed.getElement(0)*transposed.getElement(7)-transposed.getElement(6)*transposed.getElement(1))/determinant;
        elements[6] = (transposed.getElement(1)*transposed.getElement(5)-transposed.getElement(4)*transposed.getElement(2))/determinant;
        elements[7] = -(transposed.getElement(0)*transposed.getElement(5)-transposed.getElement(3)*transposed.getElement(2))/determinant;
        elements[8] = (transposed.getElement(0)*transposed.getElement(4)-transposed.getElement(3)*transposed.getElement(1))/determinant;
    }
}

Matrix3 Matrix3::getInverseMatrix(){
    Matrix3 inversed(elements);
    if(inversed.det() == 0){
        cout<<"matrice non inversible"<<endl;
    }
    else{
        inversed.inverseMatrix();
        return inversed;
    }
    return NULL;
}

Matrix3 Matrix3::operator+(Matrix3 mtx){
    Matrix3 newMtx;
    for (int i = 0; i < sizeof(elements); i++)
    {
        newMtx.setElement(elements[i]+mtx.getElement(i), i);
    }

    return newMtx;
}

Matrix3 Matrix3::operator-(Matrix3 mtx){
    Matrix3 newMtx;
    for (int i = 0; i < sizeof(elements); i++)
    {
        newMtx.setElement(elements[i]-mtx.getElement(i), i);
    }

    return newMtx;
}

Matrix3 Matrix3::operator*(Matrix3 mtx){
    Matrix3 newMtx;
    newMtx.setElement(elements[0]*mtx.getElement(0)+elements[1]*mtx.getElement(3)+elements[2]*mtx.getElement(6),0);
    newMtx.setElement(elements[0]*mtx.getElement(1)+elements[1]*mtx.getElement(4)+elements[2]*mtx.getElement(7),1);
    newMtx.setElement(elements[0]*mtx.getElement(2)+elements[1]*mtx.getElement(5)+elements[2]*mtx.getElement(8),2);


    newMtx.setElement(elements[3]*mtx.getElement(0)+elements[4]*mtx.getElement(3)+elements[5]*mtx.getElement(6),3);
    newMtx.setElement(elements[3]*mtx.getElement(1)+elements[4]*mtx.getElement(4)+elements[5]*mtx.getElement(7),4);
    newMtx.setElement(elements[3]*mtx.getElement(2)+elements[4]*mtx.getElement(5)+elements[5]*mtx.getElement(8),5);


    newMtx.setElement(elements[6]*mtx.getElement(0)+elements[7]*mtx.getElement(3)+elements[8]*mtx.getElement(6),6);
    newMtx.setElement(elements[6]*mtx.getElement(1)+elements[7]*mtx.getElement(4)+elements[8]*mtx.getElement(7),7);
    newMtx.setElement(elements[6]*mtx.getElement(2)+elements[7]*mtx.getElement(5)+elements[8]*mtx.getElement(8),8);
    return newMtx;
}

Vector3 Matrix3::operator*(Vector3 vct){
    float x = elements[0]*vct.getx() + elements[1]*vct.gety() + elements[2]*vct.getz();
    float y = elements[3]*vct.getx() + elements[4]*vct.gety() + elements[5]*vct.getz();
    float z = elements[6]*vct.getx() + elements[7]*vct.gety() + elements[8]*vct.getz();
    Vector3 newVct(x,y,z);
    return newVct;
}





