// Make sure header is only included once
#ifndef ODE_H_
#define ODE_H_

#include <vector>
#include <complex>
#include "typedefs.h"

// ODE class
class ODE {

  // Values and functions only accessible from the class internally
  private:

    // System of ordinary differential equations to solve
    std::vector<std::complex<Floattype> > 
      	(*f)(const std::complex<Floattype> x,
	     const std::vector<std::complex<Floattype> > &y);

    // Points to be evaluated
    std::vector<std::complex<Floattype> > x_list;
    
    // Limits of range to evaluate
    const std::complex<Floattype> a; // Lower
    const std::complex<Floattype> b; // Upper

    // Step size
    std::complex<Floattype> h;

    // Results stored in 2D: vector of vectors
    std::vector<std::vector<std::complex<Floattype> > > y_list;
     
    // Maximum number of steps to evaluate, defined by y size
    const Inttype n_max;

    // Accuracy requirement values
    const Floattype delta;   // Absolute
    const Floattype epsilon; // Relative

    // Tolerance estimator
    Floattype tau(const std::vector<std::complex<Floattype> > &y,
		  const std::complex<Floattype> h);

    // Runge-Kutta mid-point stepper prototype
    void rkstep12(const std::complex<Floattype> x0,
		  const std::vector<std::complex<Floattype> > &y0,
		  	std::vector<std::complex<Floattype> > &y1,
			std::vector<std::complex<Floattype> > &dy);

    // Runge-Kutta driver function parameters
    const Floattype power;
    const Floattype safety;

    // Runge-Kutta driver prototype
    void rkdriver();


  // Values and functions accessible from the outside
  public:

    // Constructor, some parameters with default values
    ODE(std::vector<std::complex<Floattype> > 
		(*f_in)(const std::complex<Floattype> x,
			const std::vector<std::complex<Floattype> > &y),
	const std::vector<std::complex<Floattype> > y_start,
	const std::complex<Floattype> a_in,
	const std::complex<Floattype> b_in,
	const Floattype h_start = 0.01f,
	const Inttype max_steps = 1e4,
        const Floattype delta_in = 1e-3f,
	const Floattype epsilon_in = 1e-3f,
	const Floattype power_in = 0.25f,
	const Floattype safety_in = 0.95f
	);

    // Return the number of steps taken
    Inttype steps();

    // Print the x- and y-values to stdout
    void print();

    // Write the x- and y-values to file
    void write(const char* filename);

};

#endif
