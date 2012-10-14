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

  cout << "\n\033[1;36m## Minimization with downhill-simplex, part A ##\033[0m\n";

  // Try amoeba on Rosenbrock's valley function
  cout << "\n\033[1;33m--- Rosenbrock's valley function ---\033[0m\n";
  int d = 2;
  vec p(2); p[0]=5; p[1]=6;
  p.print("Initial simplex is chosen around the point:");
  vector<vec> simplex;
  for(int i=0; i<d+1; ++i) 
    simplex.push_back(p);
  double dx = 1;
  for(int i=0; i<d; ++i) 
    simplex[i][i] += dx;
  amoeba A(rosenbrock, simplex);
  ncalls = 0;
  A.downhill(10.0f*eps);
  A.low().print("Lowest point:");
  cout << "Amoeba converged after " << ncalls << " calls\n"
       << "(Newton's root-finding method did this in 4181 calls)\n";

  // Try amoeba on Himmelblau's function
  cout << "\n\033[1;33m--- Himmelblau's function ---\033[0m\n";
  vec p2(2); p2[0]=5; p2[1]=6;
  p2.print("Initial simplex is chosen around the point:");
  vector<vec> simplex2;
  for(int i=0; i<d+1; ++i) 
    simplex2.push_back(p2);
  double dx2 = 1;
  for(int i=0; i<d; ++i) 
    simplex2[i][i] += dx2;
  amoeba A2(himmelblau, simplex2);
  ncalls = 0;
  A2.downhill(10.0f*eps);
  A2.low().print("Lowest point:");
  cout << "Amoeba converged after " << ncalls << " calls\n"
       << "(Newton's root-finding method did this in 33 calls)\n";

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
