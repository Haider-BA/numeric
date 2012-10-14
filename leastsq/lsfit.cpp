#include <iostream>
#include <cmath> // NaN is here
#include <armadillo>
#include "header.h"
#include "lsfit.h"
#include "qrfunc.h"

// A number of i fitting functions, evaluated at x
Floattype LSfit::fitfuncts(char i, Floattype x)
{
  // Choose function i
  switch (i) {
    case 0:
      return 1.0f;
      break;
    case 1:
      return x;
      break;
    case 2:
      return x*x;
      break;
    default:
      std::cout << "Wrong function (i = "
		<< i << ") specified in fitfuncts, x = " 
		<< x << '\n';
      return NAN;
  }
}

// Constructor
LSfit::LSfit(arma::Col<Floattype> &x,
    	     arma::Col<Floattype> &y,
	     arma::Col<Floattype> &delta_y) : n(x.n_rows), m(3), A(n,m), b(n), c(m)
{

  // Initialize b values
  b = y/delta_y;

  // Initialize A values
  for (Lengthtype i=0; i<n; ++i) {
    for (Lengthtype k=0; k<m; ++k) {
      A(i,k) = fitfuncts(k,x(i)) / delta_y(i);
    }
  }

  // Perform QR decomposition
  QR qr(A);

  // Calculate the least-squares solution
  c = qr.backsub(b);
}

// Evaluate function at x
Floattype LSfit::eval(Floattype x)
{
  // Find the linear combination of m functions to calculate F(x)
  Floattype sum = 0.0f;
  for (char k=0; k<m; ++k)
    sum += c(k) * fitfuncts(k, x);
  return sum;
}
