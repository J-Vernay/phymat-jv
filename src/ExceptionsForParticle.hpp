#include <iostream>
#include <exception>
using namespace std;

class ExceptionInverseMassInf: public exception
{
  inline virtual const char* what() const throw()
  {
    return "You cannot have an infinite inverse mass";
  }
} ;

class ExceptionNegativMass: public exception
{
  inline virtual const char* what() const throw()
  {
    return "You cannot have a negative mass";
  }
} ;

class ExceptionDampingNotPercentage: public exception
{
  inline virtual const char* what() const throw()
  {
    return "Damping must be a percentage";
  }
} ;
