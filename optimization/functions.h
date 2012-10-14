#include <functional>
#include <armadillo>
using namespace arma;
using namespace std;

int ncalls = 0;


// Rosenbrock's function
function<double(vec)> rosenbrock = [&ncalls] (vec p) {
  ++ncalls;
  double x = p[0], y = p[1];
  return (1.0f - x) * (1.0f - x) 
    	 + 100.f * (y - x*x) * (y - x*x);
};

// Himmelblau's function
function<double(vec)> himmelblau = [&ncalls] (vec p) {
  ++ncalls;
  double x = p[0], y = p[1];
  return (x*x + y - 11.0f) * (x*x + y - 11.0f)
       + (x + y*y - 7.0f) * (x + y*y - 7.0f);
};

