#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include "typedefs.h"
#include "check.h"
#include "ode.h"
#include "functions.h"

int main()
{
  // Namespace declarations
  using std::cout;
  using std::vector;
  using std::complex;

  // Calculate machine precision
  Floattype eps_machine = 1.0f;
  while (1.0f + eps_machine != 1.0f)
    eps_machine /= 2.0f;
  
  cout << "\n\033[1;33m--- Part C: Solving along a complex path ---\033[0m\n";
  complex<Floattype> a(0.0f, 0.0f);	// Lower limit
  complex<Floattype> b(2.0f*M_PI, 2.0f*M_PI); // Upper limit
  cout << "Integration path: b-a = " << b-a << '\n';
  Inttype n_eqs = 2; // Number of equations in ODE system
  vector<complex<Floattype> > y_start(n_eqs);
  complex<Floattype> y0(0.0f, 0.0f);
  complex<Floattype> y1(1.0f, 1.0f);
  y_start[0] = y0;
  y_start[1] = y1;
  Floattype h_start = 0.01f;
  ODE ode(func1,	// ODE system
	  y_start,	// Initial values
	  a,	// Lower limit
	  b,	// Upper limit
	  h_start,	// Start value of step size
	  10000,	// Max. number of steps
	  eps_machine*1e12f,  // Absolute precision
	  eps_machine*1e12f); // Relative precision
  ode.write("funcC.dat"); // Write solutions to data file

  // Report to stdout
  cout << "ODE system solved in "
       << ode.steps() << " steps.\n\n";

  // Return successfully
  return 0;
}

