#include "Vector.hpp"
#include <iostream>
using namespace std;

int main(){
    Vector3 V1 = Vector3(2,2,2);
    Vector3 V2 = Vector3(1,2,3);

    

    cout << V1.scalarProduct(V2) << endl;
    cout << V1.vectorialProduct(V2) << endl;
    return 0;
}