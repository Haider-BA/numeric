// Make sure file is only included once per object
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <vector>
#include <complex>
#include "typedefs.h"


//// ODEs with real+complex parts.
//// Return the derivatives at the point x,vec(y)

std::vector<std::complex<Floattype> >
	func1(const std::complex<Floattype> z,
	      const std::vector<std::complex<Floattype> > &y)
{
  std::vector<std::complex<Floattype> > dydz(2);
  dydz[0].real() = y[1].real();
  dydz[0].imag() = y[1].imag();
  dydz[1].real() = -y[0].real();
  dydz[1].imag() = 0.5f*y[0].imag();
  return dydz;
}

#endif
