// Make sure header is only included once
#ifndef QRFUNC_H_
#define QRFUNC_H_

#include <armadillo>
#include "header.h"

// QR structure
class QR {
  private:
    // System size
    const Lengthtype n;

  public:
    //// Data

    // Input data
    arma::mat A;

    // QR decomposition matrices
    arma::mat Q;
    arma::mat R;

    //// Prototype functions

    // Constructor prototype
    QR(arma::mat &A);

    // Destructor
    ~QR();

    // Return system size
    Lengthtype size();

    // QR decomposition of Armadillo matrix A, returning R
    // and modified A (=Q)
    void decomp();

    // Backsubstitution of triangular system
    arma::vec backsub(arma::vec &b);

    // Absolute value of the determinant of matrix R
    Floattype det();

    // Inverse of matrix A
    arma::mat inverse();
};

#endif
