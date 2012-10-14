#include <functional>
#include <armadillo>
using namespace arma;
using namespace std;

int ncalls = 0;

// System of equations (first task)
function<vec(vec)> sys_2_eqs = [&ncalls] (vec p) {
  ++ncalls;
  double A = 10000.0f;
  vec f(2);
  double x = p[0], y = p[1];
  f[0] = A * x * y - 1.0f;
  f[1] = exp(-x) + exp(-y) - 1.0f - 1.0f/A;
  return f;
};

// Rosenbrock's function
function<vec(vec)> rosenbrock = [&ncalls] (vec p) {
  ++ncalls;
  vec f(1);
  double x = p[0], y = p[1];
  f[0] = (1.0f - x) * (1.0f - x) 
    	 + 100.f * (y - x*x) * (y - x*x);
  return f;
};

// Gradient of Rosenbrock's function
function<vec(vec)> rosenbrockGrad = [&ncalls] (vec p) {
  ++ncalls;
  vec f(2);
  double x = p[0], y = p[1];
  f[0] = 2.0f * (1.0f - x) * (-1.0f)
    + 100.0f * 2.0f * (y - x*x) * (-1.0f) * 2.0f * x;
  f[1] = 100.0f * 2.0f * (y - x*x);
  return f;
};

// Return derivatives of Rosenbrock's function (Jacobian matrix)
mat rosenbrockJacobian(vec p) {
  mat J(2,2);
  double x = p[0], y = p[1];
  J(0,0) = 2.0f + 1200.0f*x*x - 400.0f*y;
  J(0,1) = -400.0f*x;
  J(1,0) = -400.0f*x;
  J(1,1) = 200.0f;
  return J;
};


// Himmelblau's function
function<vec(vec)> himmelblau = [&ncalls] (vec p) {
  ++ncalls;
  vec f(1);
  double x = p[0], y = p[1];
  f[0] = (x*x + y - 11.0f) * (x*x + y - 11.0f)
       + (x + y*y - 7.0f) * (x + y*y - 7.0f);
  return f;
};

// Gradient of Himmelblau's function
function<vec(vec)> himmelblauGrad = [&ncalls] (vec p) {
  ++ncalls;
  vec f(2);
  double x = p[0], y = p[1];
  f[0] = 2.0f * (x*x + y - 11.0f) * 2.0f * x + 2.0f*(x + y*y - 7.0f);
  f[1] = 2.0f * (x*x + y - 11.0f) + 2.0f * (x + y*y - 7.0f) * 2.0f * y;
  return f;
};

// Return derivatives of Himmelblau's function (Jacobian matrix)
mat himmelblauJacobian(vec p) {
  mat J(2,2);
  double x = p[0], y = p[1];
  J(0,0) = 4.0f * x*2.0f * x
    	 + 4.0f * (x*x + y - 11.0f) + 2.0f;
  J(0,1) = 4.0f * x+4.0f * y;
  J(1,0) = 4.0f * x+4.0f * y;
  J(1,1) = 4.0f * y * 2.0f * y
    	 + 4.0f * (y*y + x - 7.0f) + 2.0f;

  return J;
}
