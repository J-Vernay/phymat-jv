#pragma once
#include <exception>
using namespace std;

class ExceptionDeleteIndexOutOfRange: public exception
{
  inline virtual const char* what() const throw()
  {
    return "You cannot delete a particle which does not exist";
  }
} ;

class ExceptionIndexOutOfRange: public exception
{
  inline virtual const char* what() const throw()
  {
    return "Particle does not exist, index out of range";
  }
} ;

class ExceptionNegativOrNullFramerate: public exception
{
  inline virtual const char* what() const throw()
  {
    return "FrameRate must be positive and not null";
  }
} ;


