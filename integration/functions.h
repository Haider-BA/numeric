#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <cmath>
#include "header.h"

int ncalls = 0;

Floattype func1(const Floattype x)
{
  ++ncalls;
  return x*x;
}

Floattype func2(const Floattype x)
{
  ++ncalls;
  return log(x)/sqrt(x);
}

Floattype func3(const Floattype x)
{
  ++ncalls;
  return 4.0f*sqrt(1.0f-(1.0f-x)*(1.0f-x));
}

#endif
