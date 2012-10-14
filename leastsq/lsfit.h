// Make sure header is only included once per object
#ifndef LSFIT_H_
#define LSFIT_H_

#include <armadillo>
#include "header.h"

// lsfit structure
class LSfit {
  private:
    const Lengthtype n; // Input data count
    const Lengthtype m; // Fitting function count

    // Covariance matrix
    arma::Mat<Floattype> A;

    // Data points
    arma::Col<Floattype> b;

    // Fitting coefficients
    arma::Col<Floattype> c;

    // Evaluate fitting function i at x
    Floattype fitfuncts(char i, Floattype x); 

  public:

    // Constructor. Arguments: input data points
    LSfit(arma::Col<Floattype> &x,
	  arma::Col<Floattype> &y,
	  arma::Col<Floattype> &delta_y);

    // Destructor
    //~LSfit();
    
    // Return value fitted at x
    Floattype eval(Floattype x);

};

#endif
