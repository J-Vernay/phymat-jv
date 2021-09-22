#pragma once
#include <iostream>
#include <exception>
using namespace std;

class ExceptionDivideByNullComponent: public exception
{
  virtual const char* what() const throw()
  {
    return "One of the component denominator's vector is 0 : you cannot divide by 0";
  }
} ;

class ExceptionDivideByNullScalar: public exception
{
  virtual const char* what() const throw()
  {
    return "You cannot divide the component of your vector by 0";
  }
} ;