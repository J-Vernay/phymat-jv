#include "Quaternion.hpp"

    //Constructors :
    Quaternion::Quaternion(){
        this->w = 0;
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Quaternion::Quaternion(float w, float x, float y, float z){
        this->w = w;
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Quaternion::Quaternion(float w, Vector3 imaginaryNumbers){
        this->w = w;
        this->x = imaginaryNumbers.getx();
        this->y = imaginaryNumbers.gety();
        this->z = imaginaryNumbers.getz();
    }

    //Getters  :
    float Quaternion::getW() const {
        return this->w;
    } //scalar 

    float Quaternion::getX() const {
        return this->x;
    } //first imaginary number

    float Quaternion::getY() const {
        return this->y;
    } //second imaginary number


    float Quaternion::getZ() const
    {
        return this->z;
    } //third imaginary number

    Vector3 Quaternion::getImaginaryNumbers() {
        return Vector3(this->getX(), this->getY(), this->getZ());
    } //all imaginary numbers
    
    //Setters
    void Quaternion::setRealNumber(float w){
        this->w = w;
    }

    void Quaternion::setImaginaryNumbers(Vector3 imaginaryNumbers) {
        this->x = imaginaryNumbers.getx();
        this->y = imaginaryNumbers.gety();
        this->z = imaginaryNumbers.getz();
    }

    void Quaternion::setImaginaryNumbers(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    //Inverse and conjugate
    Quaternion Quaternion::getConjugate(){
        return Quaternion(this->w, -this->x, -this->y, -this->z);
    }

    Quaternion Quaternion::getInverse(){
        float squareSum = this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z;
        if(squareSum != 0) {
            return Quaternion((1/squareSum) * this->w, - (1/squareSum) * this->x, - (1/squareSum) * this->y, -(1/squareSum) * this->z);
        }
        cout << "Cannot inverse Quaternion" << endl;
        return Quaternion();
    }

    float Quaternion::getNorm(){
        return sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
    }

    //Transform the quaternion into a matrix
    Matrix3 Quaternion::quaternionIntoMatrix(){
        return Matrix3(1 - 2*(this->y*this->y + this->z*this->z), 2*(this->x*this->y + this->z*this->w), 2*(this->x*this->y - this->y*this->w), 2*(this->x*this->y - this->z*this->w), 1 - 2*(this->x*this->x + this->z*this->z) , 2*(this->z*this->y + this->x*this->w), 2*(this->z*this->x + this->y*this->w) , 2*(this->z*this->y - this->x*this->w) , 1 - 2*(this->y*this->y + this->x*this->x));
    }

    //Normalise le quaternion
    void Quaternion::normalize(){
        *this = *this * (1/getNorm());
    }
    
    //Overload of operators :
    Quaternion Quaternion::operator+(Quaternion other){
        return Quaternion(this->w + other.getW(), this->x + other.getX(), this->y + other.getY(), this->z + other.getZ());
    } // Addition

    Quaternion Quaternion::operator-(Quaternion other) {
        return Quaternion(this->w - other.getW(), this->x - other.getX(), this->y - other.getY(), this->z - other.getZ());
    } //Soustraction

    Quaternion Quaternion::operator*(Quaternion other){
        return Quaternion(this->w*other.getW() - this->x*other.getX() - this->y*other.getY() - this->z*other.getZ(), this->w*other.getX() + this->x*other.getW() + this->y*other.getZ() - this->z*other.getY(), this->w*other.getY() + this->y*other.getW() + this->z*other.getX() - this->x*other.getZ(), this->w*other.getZ() + this->z*other.getW() + this->x*other.getY() - this->y*other.getX());
    } //Multiplication

/*,,
    Quaternion Quaternion::operator^(int t){
        //qw^t q0 = 1/2 w q(t)
        return 1/2 * angularVelocity * this;
    } //Exponentiation
*/
ostream& operator<<(ostream& os, const Quaternion& q){
    os << "[" << q.getW() <<  ", (" << q.getX() << ", " << q.getY() << ", " << q.getZ() << ")]" << endl;
    return os;
}

Quaternion operator*(const float k, Quaternion q){
    return Quaternion(k * q.getW(), k * q.getX(), k * q.getY(), k * q.getZ());
}

Quaternion operator*(Quaternion q, const float k){
    return Quaternion(k * q.getW(), k * q.getX(), k * q.getY(), k * q.getZ());
}