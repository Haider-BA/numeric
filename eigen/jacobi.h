// Make sure header is only included once per object
#ifndef JACOBI_H_
#define JACOBI_H_

#include <armadillo>
#include "header.h"

// lsfit structure
class Jacobi {
  private:
    const Lengthtype n; // Matrix width and height

    // Transformed matrix A: At
    arma::Mat<Floattype> At;

    // Diagonal
    arma::Col<Floattype> e;

    // Matrix of eigenvectors
    arma::Mat<Floattype> V;

  public:

    // Constructor. Arguments: input matrix
    Jacobi(const arma::Mat<Floattype> &A);

    // Destructor
    //~Jacobi();

    // Return transformed matrix
    arma::Mat<Floattype> trans();

    // Return matrix of eigenvectors
    arma::Mat<Floattype> eigenvectors();

    // Return vector of eigenvalues
    arma::Col<Floattype> eigenvalues();
};
#endif
