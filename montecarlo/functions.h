#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "header.h"

int ncalls = 0;

Floattype functionA(const std::vector<Floattype> x) {
  if (x.size() != 3) {
    std::cout << "Error! FunctionA must be given a 3D input point!\n";
    return NAN;
  }
   
  return 1.0f / (1.0f-cos(x[0]) * cos(x[1]) * cos(x[2])) / M_PI / M_PI / M_PI;
}

#endif
