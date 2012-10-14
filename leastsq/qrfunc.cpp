#include <iostream>
#include <armadillo>
#include "header.h"
#include "qrfunc.h"

// QR decomposition constructor
QR::QR(arma::mat &A)
  : n(A.n_cols),
    A(A),
    Q(A)
{
  // Initialize output structures
  R = arma::zeros<arma::mat> (n,n);
  
  // Perform QR decomposition straight away
  decomp();
}

// Class deconstructor (equivalent to compiler destructor)
QR::~QR() { };

// Return system size
Lengthtype QR::size()
{
  return n;
}

// QR decomposition function of Armadillo matrix.
// Returns right matrix R, and modifies A into Q.
// Uses Gram-Schmidt orthogonalization
void QR::decomp()
{
  Floattype r, s;
  Lengthtype j;
  for (Lengthtype i=0; i<n; ++i) {
    r = dot(Q.col(i), Q.col(i));
    R(i,i) = sqrt(r);
    Q.col(i) /= sqrt(r); // Normalization
    for (j=i+1; j<n; ++j) {
      s = dot(Q.col(i), Q.col(j));
      Q.col(j) -= s*Q.col(i); // Orthogonalization
      R(i,j) = s;
    }
  }
}

// Solve the square system of linear equations with back
// substitution. T is an upper triangular matrix.
arma::vec QR::backsub(arma::vec &b)
{
  Floattype tmpsum;
  arma::vec x = Q.t() * b;
  for (Lengthtype i=n-1; i>=0; --i) {
    tmpsum = 0.0f;
    for (Lengthtype k=i+1; k<n; ++k) 
      tmpsum += R(i,k) * x(k);

    x(i) = 1.0f/R(i,i) * (x(i) - tmpsum);
  }
  return x;
}

// Calculate the (absolute value of the) determinant of 
// matrix A given the Q and R components.
// det(A) = det(Q) * det(R), |det(Q) = 1|
// => |det(A)| = |det(R)|
Floattype QR::det()
{
  Floattype determinant = 1.0f;
  for (Lengthtype i=0; i<n; ++i) 
    determinant *= R(i,i);
  return fabs(determinant);
}

// Calculate the inverse of matrix A given the Q and R
// components.
arma::mat QR::inverse()
{
  arma::mat inv = arma::zeros<arma::mat> (n, n);
  // In vector z, all elements are equal to 0, except z(i) = 1
  arma::vec z = arma::zeros<arma::mat> (n);

  for (Lengthtype i=0; i<n; ++i) {
    z(i) = 1.0f; // Element i changed to 1
    inv.col(i) = backsub(z);
    z(i) = 0.0f; // Element i changed back to 0
  }

  return inv;
}
