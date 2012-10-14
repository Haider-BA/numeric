// Make sure header is only included once
#ifndef VECTOR_ARITHMETIC_H_
#define VECTOR_ARITHMETIC_H_

#include <vector>
#include <cmath> // for sqrt
#include "typedefs.h"

//// Overload vector methods to allow scalar-
//// and element-wise arithmetic operations

// Scalar multiplication (same scalar for real and imaginary parts)
std::vector<std::complex<Floattype> > 
	operator*(const std::vector<std::complex<Floattype> > vec,
    		  const Floattype scalar)
{
  std::vector<std::complex<Floattype> > result(vec.size());
  for (Inttype i=0; i<vec.size(); ++i) {
    result[i].real() = real(vec[i])*scalar;
    result[i].imag() = imag(vec[i])*scalar;
  }
  return result;
}

// Scalar multiplication
std::vector<std::complex<Floattype> > 
	operator*(const std::vector<std::complex<Floattype> > vec,
    		  const std::complex<Floattype> scalar)
{
  std::vector<std::complex<Floattype> > result(vec.size());
  for (Inttype i=0; i<(Inttype)vec.size(); ++i)
    result[i] = vec[i]*scalar;
  return result;
}

// Scalar division 
std::vector<std::complex<Floattype> > 
	operator/(const std::vector<std::complex<Floattype> > vec,
    		  const std::complex<Floattype> scalar)
{
  std::vector<std::complex<Floattype> > result(vec.size());
  for (Inttype i=0; i<(Inttype)vec.size(); ++i)
    result[i] = vec[i]/scalar;
  return result;
}

// Element-wise addition
std::vector<std::complex<Floattype> > 
	operator+(const std::vector<std::complex<Floattype> > vec1, 
    		  const std::vector<std::complex<Floattype> > vec2)
{
  std::vector<std::complex<Floattype> > result(vec1.size());
  for (Inttype i=0; i<(Inttype)vec1.size(); ++i)
    result[i] = vec1[i] + vec2[i];
  return result;
}

// Element-wise subtraction
std::vector<std::complex<Floattype> > 
	operator-(const std::vector<std::complex<Floattype> > vec1,
    		  const std::vector<std::complex<Floattype> > vec2)
{
  std::vector<std::complex<Floattype> > result(vec1.size());
  for (Inttype i=0; i<(Inttype)vec1.size(); ++i)
    result[i] = vec1[i] - vec2[i];
  return result;
}

// Element-wise multiplication
std::vector<std::complex<Floattype> >
	operator*(const std::vector<std::complex<Floattype> > vec1,
	    	  const std::vector<std::complex<Floattype> > vec2)
{
  std::vector<std::complex<Floattype> > result(vec1.size());
  for (Inttype i=0; i<(Inttype)vec1.size(); ++i)
    result[i] = vec1[i] * vec2[i];
  return result;
}

// Normalize vector
Floattype cnorm(const std::vector<std::complex<Floattype> > vec)
{
  Floattype res = 0.0f;
  for (Inttype i=0; i<(Inttype)vec.size(); ++i)
    res += norm(vec[i])*norm(vec[i]);
  return sqrt(res);
}

#endif
