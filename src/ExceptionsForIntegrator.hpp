#pragma once
#include <exception>
using namespace std;

class ExceptionDeleteIndexOutOfRange: public exception
{
  virtual const char* what() const throw()
  {
    return "You cannot delete a particle which does not exist";
  }
} ExceptionDeleteIndexOutOfRange;

class ExceptionNegativOrNullFramerate: public exception
{
  virtual const char* what() const throw()
  {
    return "FrameRate must be positive and not null";
  }
} ExceptionNegativOrNullFramerate;


