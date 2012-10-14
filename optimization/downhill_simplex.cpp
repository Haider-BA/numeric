#include <iostream>
#include <armadillo>
#include <vector>
#include <functional>
#include "downhill_simplex.h"

using namespace std;
using namespace arma;

// Amoeba constructor
amoeba::amoeba(function<double(vec)> fun, vector<vec> simplex)
  : d(simplex.size()-1), f(fun), value(zeros<vec>(d)), p_ce(zeros<vec>(d))
{
  p_ce_o = p_ce;

  for (int i=0; i<d+1; ++i)
    p.push_back(simplex[i]);
  for (int i=0; i<d+1; ++i)
    value[i] = f(p[i]);

  update();

}

// Update amoeba parameters
void amoeba::update()
{

  p_ce_o = p_ce;

  // Find highest point
  hi = 0;
  for (int i=1; i<d+1; ++i)
    if (value[i] > value[hi])
      hi = i;

  // Find lowest point
  lo = 0;
  for (int i=1; i<d+1; ++i)
    if (value[i] < value[lo])
      lo = i;

  // Find centroid
  p_ce = zeros<vec>(d);
  for (int i=0; i<d+1; ++i)
    if (i != hi)
      p_ce += p[i];
  p_ce /= d;

  // Write amoeba position to stderr
  pos();
}

// Find size of simplex
double amoeba::size()
{
  double s = 0;
  for (int i=0; i<d+1; ++i)
    if (i != lo) {
      double n = norm(p[i] - p[lo], 2.0f);
      if (n>s)
	s=n;
    }
  return s;
}

void amoeba::downhill(double simplex_size_goal)
{
  // Find operation to update position
  while (size() > simplex_size_goal) {

    vec p_re = p_ce + (p_ce - p[hi]); // Try reflection
    double f_re = f(p_re);
    if (f_re < value[lo]) {
      vec p_ex = p_ce + 1.0f * (p_ce - p[hi]); // Try expansion
      double f_ex = f(p_ex);
      if (f_ex < f_re) {
	value[hi] = f_ex;
	p[hi] = p_ex; // Accept expansion
	update(); continue; // Start loop over
      }
    }

    if (f_re < value[hi]) {
      value[hi] = f_re;
      p[hi] = p_re; // Accept reflection
      update(); continue; // Start loop over
    }

    vec p_co = p_ce + 0.5f * (p[hi] - p_ce); // Try contraction
    double f_co = f(p_co);
    if (f_co < value[hi]) {
      value[hi] = f_co;
      p[hi] = p_co; // Accept contraction
      update(); continue; // Start loop over
    }

    for (int i=0; i<d+1; ++i)
      if (i != lo) {
	p[i] = 0.5f * (p[i] + p[lo]); // Do reduction
	value[i] = f(p[i]);
      }
    update(); continue;
  }
}

void amoeba::downhill_mod(double simplex_size_goal)
{
  // Find operation to update position
  while (size() > simplex_size_goal) {

    vec p_re = p_ce + (p_ce - p[hi]); // Try reflection

    double f_re = f(p_re);
    if (f_re < value[lo]) {
      vec p_ex_n = p_ce + 1.0f * (p_ce - p[hi]); // Try expansion
      double f_ex_n = f(p_ex_n);
      vec p_ex_o = p_ce_o + 1.0f * (p_ce_o - p[hi]); // Try expansion, old val
      double f_ex_o = f(p_ex_o);

      // Find out which expansion gave the lowest value
      vec p_ex; double f_ex;
      if (f_ex_n < f_ex_o) { // New val
	p_ex = p_ex_n;
	f_ex = f_ex_n;
      } else { // Old val
	p_ex = p_ex_o;
	f_ex = f_ex_o;
      }

      if (f_ex < f_re) {
	value[hi] = f_ex;
	p[hi] = p_ex; // Accept expansion
	update(); continue; // Start loop over
      }
    }

    if (f_re < value[hi]) {
      value[hi] = f_re;
      p[hi] = p_re; // Accept reflection
      update(); continue; // Start loop over
    }

    vec p_co = p_ce + 0.5f * (p[hi] - p_ce); // Try contraction
    double f_co = f(p_co);
    if (f_co < value[hi]) {
      value[hi] = f_co;
      p[hi] = p_co; // Accept contraction
      update(); continue; // Start loop over
    }

    for (int i=0; i<d+1; ++i)
      if (i != lo) {
	p[i] = 0.5f * (p[i] + p[lo]); // Do reduction
	value[i] = f(p[i]);
      }
    update(); continue;
  }
}

// Write simplex points to stderr
void amoeba::pos()
{
  for (int i=0; i<d+1; ++i)
    std::cerr << p[i][0] << '\t'
              << p[i][1] << '\n';
}

// Return lowest point of simplex
vec amoeba::low()
{
  return p[lo];
}
