#include <iostream>
#include <cmath>
#include <armadillo>
#include "header.h"
#include "jacobi.h"

// Constructor: Perform rotation straight away
Jacobi::Jacobi(const arma::Mat<Floattype> &A)
		: n(A.n_rows), At(A), e(n), V(n,n)
{
  // Initialize diagonal vector to be filled with eigenvalues
  e = A.diag();

  // Set main diagonal values to 1, off-diagonal values to 0
  V.eye();

  Lengthtype p, q, i; // Iterator vars
  int changed;
  Lengthtype rotations = 0; // Number of rotations performed

  // Cell value variables, used as local storage for mat/vec vals.
  Floattype app, aqq, apq, phi, c, s, app1, aqq1;
  Floattype aip, api, aiq, aqi, vip, viq;

  do {
    changed = 0;
    for (p=0; p<n; ++p) { // Row iteration
      for (q=p+1; q<n; ++q) { // Cols right of diagonal
	
	// Initialize cell-relevant data
	app = e(p);
	aqq = e(q);
	apq = At(p,q);
	phi = 0.5f * atan2(2.0f * apq, aqq-app);
	c = cos(phi);
	s = sin(phi);
	app1 = c*c * app - 2.0f * s * c * apq + s*s * aqq;
	aqq1 = s*s * app + 2.0f * s * c * apq + c*c * aqq;

	if (app1 != app || aqq1 != aqq) {
	  changed = 1;
	  ++rotations;
	  e(p)    = app1;
	  e(q)    = aqq1;
	  At(p,q) = 0.0f;

	  for (i = 0; i<p; ++i) {
	    aip = At(i,p);
	    aiq = At(i,q);
	    At(i,p) = c * aip - s * aiq;
	    At(i,q) = c * aiq + s * aip;
	  }

	  for (i=p+1; i<q; ++i) {
	    api = At(p,i);
	    aiq = At(i,q);
	    At(p,i) = c * api - s * aiq;
	    At(i,q) = c * aiq + s * api;
	  }

	  for (i=q+1; i<n; ++i) {
	    api = At(p,i);
	    aqi = At(q,i);
	    At(p,i) = c * api - s * aqi;
	    At(q,i) = c * aqi + s * api;
	  }

	  for (i=0; i<n; ++i) {
	    vip = V(i,p);
	    viq = V(i,q);
	    V(i,p) = c * vip - s * viq;
	    V(i,q) = c * viq + s * vip;
	  }
	
	} // if end
      } // q loop end
    } // p loop end
  } while (changed != 0); // do-while end

  // Make transformed matrix symmetric 
  At = arma::symmatu(At);

  if (verbose == true)
    std::cout << "\nPerformed " << rotations << " Jacobi rotations.\n";
}

// Return transformed matrix
arma::Mat<Floattype> Jacobi::trans()
{
  return At;
}

// Return matrix of eigenvectors
arma::Mat<Floattype> Jacobi::eigenvectors()
{
  return V;
}

// Return vector of eigenvalues
arma::Col<Floattype> Jacobi::eigenvalues()
{
  return e;
}
