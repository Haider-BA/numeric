#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
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

  cout << "\n\033[1;33m--- Part D: Precision analysis ---\033[0m\n";
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

  vector<Floattype> precs; // Vector containing precision values
  vector<Inttype>   steps; // Vector containing number of steps required

  for (Floattype prec=eps_machine*10.0f; prec<0.1f; prec *= 10.0f) {
    ODE ode(func1,	// ODE system
	    y_start,	// Initial values
	    a,		// Lower limit
	    b,		// Upper limit
	    h_start,	// Start value of step size
	    100000,	// Max. number of steps
	    prec,  	// Absolute precision
	    prec); 	// Relative precision
    precs.push_back(prec); 	  // Save precision
    steps.push_back(ode.steps()); // Save number of steps taken
  }

  // Save results to text file
  std::ofstream ost; // Out stream object
  ost.open("funcD.dat"); // Open outfile for write
  if (!ost) {
    std::cerr << "Error, can't open output file!\n";
    return 1;
  }
  // Write output values
  for (Inttype i=0; i<precs.size(); ++i)
    ost << precs[i] << '\t' << steps[i] << '\n';

  // Close file
  ost.close();

  // Return successfully
  return 0;
}
