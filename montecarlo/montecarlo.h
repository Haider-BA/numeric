#ifndef MONTECARLO_H_
#define MONTECARLO_H_

#include <vector>
#include "header.h"

class MC {

  private:

    // Length of vectors
    const Lengthtype d;

    // Function to be evaluated (pointer to function)
    Floattype (*f)(const std::vector<Floattype>);

    // Integral limits in dimension d
    const std::vector<Floattype> a;
    const std::vector<Floattype> b;

    // n-dimensional point
    std::vector<Floattype> x;

    // Number of samples
    const Lengthtype N;

    // Integration result
    Floattype Q;

    // Error
    Floattype err;

    // Volume
    Floattype V;
    void set_volume();

    // Draw random position in sample space
    std::vector<Floattype> random_x();

  public:

    // Constructor
    MC(Floattype (*function)(const std::vector<Floattype>),
       const std::vector<Floattype> a_in,
       const std::vector<Floattype> b_in,
       const Lengthtype N_in);

    // Plain Monte Carlo integrator
    void plain();

    // Print result and error
    void show();

    // Return the error
    Floattype error();
};

#endif
