#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include <string>
#include "header.h"

class Integral {

  private:

    // Input function (maybe to be transformed)
    Floattype (*f_in)(const Floattype);

    // Function to be evaluated (pointer to function)
    Floattype (*f)(const Floattype);

    // Integral limits
    Floattype low; // Lower
    Floattype high; // Upper

    // Accuracy requirement values
    const Floattype acc_pres; // Absolute
    const Floattype eps; // Relative

    // Number of recursions
    Lengthtype nrec;

    // Adaptive integrator function to be
    // called recursively
    Floattype adapt(const Floattype a,
		    const Floattype b,
		    const Floattype acc,
		    const Floattype f2,
		    const Floattype f3);

    // Result of integral
    Floattype res;

    // Size of error
    Floattype err;

    // Functions for variable transformations 
    // when one or both limits are infinite
    Floattype infinf(const Floattype t); // a=inf
    Floattype fininf(const Floattype t); // b=inf
    Floattype inffin(const Floattype t); // a=inf,b=inf


  public:

    // Constructor
    Integral(Floattype (*function)(const Floattype),
	     const Floattype lower_limit,
	     const Floattype upper_limit,
	     const Floattype absolute_accuracy,
	     const Floattype relative_accuracy);

    // Return value of result
    Floattype result();

    // Return number of recursions taken
    Lengthtype recursions();

    // Print results and statistics
    void show(const std::string function_description);
};

#endif
