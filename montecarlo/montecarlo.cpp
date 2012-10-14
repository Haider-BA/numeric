#include <iostream>
#include <vector>
#include <cstdlib> // for random functionality
#include <cmath> // NaN
#include "header.h"
#include "montecarlo.h"

// Constructor
MC::MC(Floattype (*function)(const std::vector<Floattype>),
       const std::vector<Floattype> a_in,
       const std::vector<Floattype> b_in,
       const Lengthtype N_in)
  : d(a_in.size()), f(function), a(a_in), b(b_in), x(d), N(N_in)
{
  // Check that problem is at least 1D
  if (d < 1)
    std::cerr << "Error! Problem must be at least 1D\n";

  // Check that the user has specified at least 1 random sample
  if (N < 1)
    std::cerr << "Error! The algorithm should evaluate at least 1 point!\n";

  // Check input data
  for (Lengthtype i=0; i<d; ++i)
    if (a[i] >= b[i])
      std::cerr << "Error! a >= b in dimension " << i << '\n'; 

  // Initialize result and error to NaN
  Q = NAN;
  err = NAN;
}

// Plain Monte Carlo integrator
void MC::plain()
{

  // Set volume of sample space
  set_volume();

  Floattype sum = 0.0f, sumsum = 0.0f, fx;

  for (Lengthtype i=0; i<N; ++i) {
    x = random_x(); // Random sample point inside intervals
    fx = f(x);
    sum += fx;
    sumsum += fx*fx;
  }

  Floattype average  = sum/N;
  Floattype variance = sumsum/N - average*average;

  // Write results
  Q = average * V;
  err = sqrt(variance/N)*V;
}


// Calculate volume by multiplying interval in each dimension
void MC::set_volume()
{
  V = 1.0f;
  for (Lengthtype i=0; i<d; ++i)
    V *= b[i] - a[i];
}

// Draw pseudo-random position in sample space
std::vector<Floattype> MC::random_x()
{
  std::vector<Floattype> pos(d);
  for (Lengthtype i=0; i<d; ++i) {
    // Random number in [a;b] interval in dimension
    pos[i] = (b[i] - a[i]) * ((Floattype)rand()/RAND_MAX) + a[i];
  }
  return pos;
}


// Print results
void MC::show()
{
  std::cout << "Integral Q = " << Q << ", error = " << err << '\n';
}

// Return the error
Floattype MC::error()
{
  return err;
}
