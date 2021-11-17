#include "Matrix3.hpp"

int main(int argc, char const *argv[])
{
    Matrix3 matrice(1,0,0,1,1,1,1,0,1);
    matrice.inverseMatrix();
    for(int i=0; i<9;i++){
        std::cout<<matrice.getElement(i)<<std::endl;
    }
    return 0;
}
