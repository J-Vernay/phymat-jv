#include <iostream>
#include <exception>
using namespace std;

class ExceptionInverseMassInf: public exception
{
  virtual const char* what() const throw()
  {
    return "You cannot have an infinite inverse mass";
  }
} ExceptionInverseMassInf;

class ExceptionNegativMass: public exception
{
  virtual const char* what() const throw()
  {
    return "You cannot have a negative mass";
  }
} ExceptionNegativMass;

class ExceptionDampingNotPercentage: public exception
{
  virtual const char* what() const throw()
  {
    return "Damping must be a percentage";
  }
} ExceptionDampingNotPercentage;
