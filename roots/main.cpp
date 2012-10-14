#include <iostream>
#include <armadillo>
#include <functional>
#include "header.h"
#include "functions.h"
using namespace arma;
using namespace std;

vec newton(function<vec(vec)> f, vec x_0, vec dx, Floattype eps);
vec newtonJac(function<vec(vec)> f, vec x_0, vec dx, Floattype eps,
    	      mat (*J)(vec));

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Calculate machine precision
  Floattype eps = 1.0f;
  while (1.0f + eps != 1.0f)
    eps /= 2.0f;

  cout << "\nFinding the solution to the two-equation linear system:\n";
  vec x1(2); x1[0] = 2.0f; x1[1] = 2.1f;
  vec dx1(2); dx1[0] = 1e-6f; dx1[1] = 1e-6f;
  ncalls = 0;
  vec root1  = newton(sys_2_eqs, x1, dx1, eps*10.f);
  root1.print("Solution x:");
  sys_2_eqs(root1).print("f(x):");
  cout << "It took " << ncalls << " function calls\n";

  cout << "\nFinding the minumum of the Rosenbrock's valley function:\n";
  vec x2(2); x2[0] = 5.0f; x2[1] = 6.0f;
  vec dx2(2); dx2[0] = 1e-6f; dx2[1] = 1e-6f;
  ncalls = 0;
  vec root2 = newton(rosenbrockGrad, x2, dx2, eps*10.f);
  root2.print("Solution x:");
  rosenbrock(root2).print("Rosenbrock at x:");
  cout << "It took " << ncalls << " function calls\n";

  cout << "\nFinding the minumum of the Rosenbrock's valley function, Jacobian matrix predefined:\n";
  vec x2J(2); x2J[0] = 5.0f; x2J[1] = 6.0f;
  vec dx2J(2); dx2J[0] = 1e-6f; dx2J[1] = 1e-6f;
  ncalls = 0;
  vec root2J = newtonJac(rosenbrockGrad, x2J, dx2J, eps*10.f, rosenbrockJacobian);
  root2J.print("Solution x, Jacobian:");
  rosenbrock(root2J).print("Rosenbrock at x, Jacobian:");
  cout << "It took " << ncalls << " function calls\n";

  cout << "\nFinding the minumum of the Himmelblau's function:\n";
  vec x3(2); x3[0] = 5.0f; x3[1] = 6.0f;
  vec dx3(2); dx3[0] = 1e-6f; dx3[1] = 1e-6f;
  ncalls = 0;
  vec root3 = newton(himmelblauGrad, x3, dx3, eps*10.f);
  root3.print("Solution x:");
  himmelblau(root3).print("Himmelblau at x:");
  cout << "It took " << ncalls << " function calls\n";

  cout << "\nFinding the minumum of the Himmelblau's function, Jacobian matrix predefined:\n";
  vec x3J(2); x3J[0] = 5.0f; x3J[1] = 6.0f;
  vec dx3J(2); dx3J[0] = 1e-6f; dx3J[1] = 1e-6f;
  ncalls = 0;
  vec root3J = newtonJac(himmelblauGrad, x3, dx3, eps*10.f, himmelblauJacobian);
  root3J.print("Solution x:");
  himmelblau(root3J).print("Himmelblau at x, Jacobian:");
  cout << "It took " << ncalls << " function calls\n";

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
