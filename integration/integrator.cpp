#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <typeinfo>
#include "integrator.h"
#include "header.h"

// Constructor
Integral::Integral(Floattype (*function)(const Floattype),
		   const Floattype lower_limit,
		   const Floattype upper_limit,
		   const Floattype absolute_accuracy,
		   const Floattype relative_accuracy)
 : f_in(function), acc_pres(absolute_accuracy), eps(relative_accuracy)
{
  // Initialize number of recursions to 0
  nrec = 0;

  // Test whether input interval has infinite limits
  if (std::isinf(lower_limit) == 1 && std::isinf(upper_limit) == 1) {
    f = Integral::infinf;
    low = 0.0f; high = 1.0f;
  } else if (std::isinf(lower_limit) == 0 && std::isinf(upper_limit == 1)) {
    f = Integral::fininf;
    low = 0.0f; high = 1.0f;
  } else if (std::isinf(lower_limit) == 1 && std::isinf(upper_limit == 0)) {
    f = &Integral::inffin;
    low = 0.0f; high = 1.0f;
  } else {
    f = Integral::f_in;
    low = lower_limit;
    high = upper_limit;
  }

  Floattype f2 = f(low + 2.0f * (high-low)/6.0f);
  Floattype f3 = f(low + 4.0f * (high-low)/6.0f);

  res = adapt(low, high, acc_pres, f2, f3);
}

// Adaptive integrator, to be called recursively
Floattype Integral::adapt(const Floattype a,
    			  const Floattype b,
			  const Floattype acc,
			  const Floattype f2,
    			  const Floattype f3)
{
  if (nrec > 2147483647)
    return NAN; // Return NaN if recursions seem infinite

  // Function value at end points
  Floattype f1 = f(a + 1.0f * (b-a)/6.0f);
  Floattype f4 = f(b + 5.0f * (b-a)/6.0f);

  // Quadrature rules
  Floattype Q = (2.0f*f1 + f2 + f3 + 2.0f*f4) / 6.0f * (b-a);
  Floattype q = (f1 + f2 + f3 + f4) / 4.0f * (b-a);

  Floattype tolerance = acc + eps*fabs(Q);
  err = fabs(Q-q);

  // Evaluate whether result is precise 
  // enough to fulfill criteria
  if (err < tolerance)
    return Q;
  else { // Perform recursions in lower and upper interval
    ++nrec;
    Floattype q1 = adapt(a, a+(b-a)/2.0f, acc/sqrt(2), f1, f2);
    ++nrec;
    Floattype q2 = adapt(a+(b-a)/2.0f, b, acc/sqrt(2), f3, f4);
    return q1+q2;
  }
}

// Return result
Floattype Integral::result()
{
  return res;
}

// Return the number of recursions taken
Lengthtype Integral::recursions()
{
  return nrec;
}

// Print results of function integration
void Integral::show(const std::string function_description)
{
  std::cout << "Integral of function '"
            << function_description
	    << "' in interval ["
	    << low << ";" << high << "] is "
	    << res << ",\n"
	    << "with an absolute accuracy of "
	    << acc_pres
	    << " and a relative accuracy of "
	    << eps << ".\n"
	    << "Integral calculated in "
	    << nrec << " recursions, error is "
	    << err << ".\n";
}

// Functions for variable transformations when limits are infinite
Floattype Integral::infinf(const Floattype t) 
{
  return (f_in((1.0f - t) / t) + f_in(-(1.0f - t) / t)) / (t*t);
}

Floattype Integral::fininf(const Floattype t) 
{
  return f_in(low + (1.0f - t) / t) / (t*t);
}

Floattype Integral::inffin(const Floattype t) 
{
  return f_in(high - (1.0f - t) / t) / (t*t);
}

