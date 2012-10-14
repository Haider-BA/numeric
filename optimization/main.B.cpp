#include <iostream>
#include <armadillo>
#include <functional>
#include "header.h"
#include "functions.h"
#include "downhill_simplex.h"
using namespace arma;
using namespace std;

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Calculate machine precision
  double eps = 1.0f;
  while (1.0f + eps != 1.0f)
    eps /= 2.0f;

  cout << "\n\033[1;36m## Minimization with downhill-simplex, part B ##\033[0m\n";

  // Try amoeba on Rosenbrock's valley function
  cout << "\n\033[1;33m--- Rosenbrock's valley function ---\033[0m\n";
  int d = 2;
  vec p(2); p[0]=5; p[1]=6;
  if (verbose == true)
    p.print("Initial simplex is chosen around the point:");
  vector<vec> simplex;
  vector<vec> simplex_mod;
  for(int i=0; i<d+1; ++i) { 
    simplex.push_back(p);
    simplex_mod.push_back(p);
  }
  double dx = 1;
  for(int i=0; i<d; ++i) {
    simplex[i][i] += dx;
    simplex_mod[i][i] += dx;
  }
  amoeba A(rosenbrock, simplex);
  ncalls = 0;
  A.downhill(10.0f*eps);
  if (verbose == true)
    A.low().print("Lowest point:");
  cout << "Amoeba converged after " << ncalls << " calls\n";
  amoeba A_mod(rosenbrock, simplex_mod);
  ncalls = 0;
  A_mod.downhill_mod(10.0f*eps);
  if (verbose == true)
    A_mod.low().print("Lowest point (modified downhill)");
  cout << "Amoeba converged after " << ncalls << " calls with modified method\n";


  // Try amoeba on Himmelblau's function
  cout << "\n\033[1;33m--- Himmelblau's function ---\033[0m\n";
  vec p2(2); p2[0]=5; p2[1]=6;
  if (verbose == true)
    p2.print("Initial simplex is chosen around the point:");
  vector<vec> simplex2;
  vector<vec> simplex2_mod;
  for(int i=0; i<d+1; ++i) {
    simplex2.push_back(p2);
    simplex2_mod.push_back(p2);
  }
  double dx2 = 1;
  for(int i=0; i<d; ++i) {
    simplex2[i][i] += dx2;
    simplex2_mod[i][i] += dx2;
  }
  amoeba A2(himmelblau, simplex2);
  ncalls = 0;
  A2.downhill(10.0f*eps);
  if (verbose == true)
    A2.low().print("Lowest point:");
  cout << "Amoeba converged after " << ncalls << " calls\n";
  amoeba A2_mod(himmelblau, simplex2_mod);
  ncalls = 0;
  A2_mod.downhill_mod(10.0f*eps);
  if (verbose == true)
    A2_mod.low().print("Lowest point (modified downhill)");
  cout << "Amoeba converged after " << ncalls << " calls with modified method\n";

  // Return successfully
  return 0;
}

void check(const bool statement)
{
  using std::cout;
  if (statement == true)
    cout << "\t\033[0;32mPassed\033[0m\n";
  else
    cout << "\t\033[1;31mFail!!\033[0m\n";
}
