#include "Matrix3.hpp"

int main()
{
    Matrix3 matrice(1,0,0,1,1,1,1,0,1);
    //matrice.transposeMatrix();
    Matrix3 m2 = matrice.getInverseMatrix();
    //std::cout<<"ouiii"<<std::endl;
    //matrice.inverseMatrix();
    for(int i=0; i<9;i++){
        //std::cout<<"oui"<<std::endl;
        std::cout<<m2.getElement(i)<<std::endl;
    }
    
    std::cout<<"ouiii"<<std::endl;
    return 0;
}