#include <iostream>
#include <vector>
#include <cmath>  // for sqrt and pow
#include <fstream>
#include "typedefs.h"
#include "ode.h"
#include "vector_arithmetic.h"

// Constructor
ODE::ODE(std::vector<std::complex<Floattype> > 
    		(*f_in)(const std::complex<Floattype> x,
			const std::vector<std::complex<Floattype> > &y),
	 const std::vector<std::complex<Floattype> > y_start,
	 const std::complex<Floattype> a_in,
	 const std::complex<Floattype> b_in,
	 const Floattype h_start,
	 const Inttype max_steps,
	 const Floattype delta_in,
	 const Floattype epsilon_in,
	 const Floattype power_in,
	 const Floattype safety_in)
  : f(f_in),
    a(a_in), b(b_in),
    h((b_in-a_in)*h_start),
    n_max(max_steps),
    delta(delta_in), epsilon(epsilon_in),
    power(power_in), safety(safety_in)
{
  x_list.push_back(a);
  y_list.push_back(y_start);

  // Perform integration
  rkdriver();
}


// Estimate tolerance
Floattype ODE::tau(const std::vector<std::complex<Floattype> > &y,
		   const std::complex<Floattype> h_i)
{
  return abs((epsilon * cnorm(y) + delta) * sqrt(h_i/(b-a)));
}

// Runge-Kutta mid-point stepper
void ODE::rkstep12(const std::complex<Floattype> x0,
    		   const std::vector<std::complex<Floattype> > &y0,
		   std::vector<std::complex<Floattype> > &y1,
		   std::vector<std::complex<Floattype> > &dy)
{
  // Denominator 2 used in arithmetic operations
  const std::complex<Floattype> den2 (2.0f,2.0f);

  // Evaluate function at two points
  (void)f(x0,y0);
  const std::vector<std::complex<Floattype> > k0  = f(x0,y0);
  const std::vector<std::complex<Floattype> > k12 = f(x0 + h/den2, y0 + k0*h/den2);

  // Write results to output vectors
  y1 = y0 + k12*h;
  dy = (k0 - k12) * h/den2;
}


// ODE driver with adaptive step size control
void ODE::rkdriver() 
{
  std::vector<std::complex<Floattype> > dy(n_max);
  std::vector<std::complex<Floattype> > y1(n_max);

  std::complex<Floattype> x;
  Floattype err, tol;
  std::vector<std::complex<Floattype> > y;

  while (x_list.back().real() < b.real()
      || x_list.back().imag() < b.imag())
  {
    // Get values for this step
    x = x_list.back();
    y = y_list.back();

    // Make sure we don't step past the upper boundary
    if ((x + h).real() > b.real()
     || (x + h).imag() > b.imag())
      h = b - x;

    // Run Runge-Kutta mid-point stepper
    rkstep12(x, y, y1, dy);

    // Determine whether the step should be accepted
    err = cnorm(dy); // Error estimate
    tol = tau(y, h); // Tolerance
    if (err < tol) { // Step accepted
      x_list.push_back(x+h);
      y_list.push_back(y1);
    }

    // Check that we havn't hit the max. number of steps
    if (x_list.size() == n_max) {
      std::cerr << "Error, the max. number of steps "
		<< "was insufficient\n"
		<< "Try either increasing the max. number "
		<< "of steps, or decreasing the precision "
		<< "requirements\n";
      return;
    }

    // Determine new step size
    std::complex<Floattype> multiplicator (2.0f, 2.0f);
    if (err > 0.0f)
      h = h*pow(tol/err, power) * safety;
    else
      h = multiplicator*h;
  }
}


// Return the number of steps taken
Inttype ODE::steps()
{
  return x_list.size();
}

void ODE::print()
{
  for (Inttype i=0; i<x_list.size(); ++i) {
    std::cout << x_list[i] << '\t';
    for (Inttype j=0; j<y_list[0].size(); ++j)
      std::cout << y_list[i][j] << '\t';
    std::cout << '\n';
  }
}

// Write the x- and y-values to file
void ODE::write(const char* filename)
{
  std::ofstream outstream;

  // Open outfile for write
  outstream.open(filename);
  if (!outstream) {
    std::cerr << "Error, can't open output file '"
              << filename << "'.\n";
    return;
  }

  // Write output values
  for (Inttype i=0; i<x_list.size(); ++i) {
    outstream << x_list[i].real() << '\t';
    outstream << x_list[i].imag() << '\t';
    for (Inttype j=0; j<y_list[0].size(); ++j) {
      outstream << y_list[i][j].real() << '\t';
      outstream << y_list[i][j].imag() << '\t';
    }
    outstream << '\n';
  }

  // Close file
  outstream.close();

  if (verbose == true)
    std::cout << "Output written in '" << filename << "'.\n";
}  

