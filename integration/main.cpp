#include <iostream>
#include "header.h"
#include "functions.h"
#include "integrator.h"

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Calculate machine precision
  Floattype eps_machine = 1.0f;
  while (1.0f + eps_machine != 1.0f)
    eps_machine /= 2.0f;

  Floattype a, b, acc, eps;

  // Find the integral of function 1
  a = 0.0f, b = 1.0f;
  acc = 0.001f; eps = acc;
  ncalls = 0;
  Integral F1(func1, a, b, acc, eps);
  F1.show("f(x) = x*x");
  cout << '\n';

  // Find the integral of function 2
  a = 1e-8f, b = 1.0f;
  acc = 0.001f; eps = acc;
  ncalls = 0;
  Integral F2(func2, a, b, acc, eps);
  F2.show("f(x) = log(x)/sqrt(x)");
  cout << "Check: Integral equal to -4:\t";
  check(fabs(F2.result() + 4.0f) < 0.1f);
  cout << '\n';

  // Find the integral of function 3
  a = 0.0f, b = 1.0f;
  acc = 1e-8f; eps = acc;
  ncalls = 0;
  Integral F3(func3, a, b, acc, eps);
  F3.show("f(x) = 4*sqrt(1-(1-x)^2)");
  cout << "Check: Integral equal to pi:\t";
  check(fabs(F3.result() - M_PI) < 0.01f);
  cout << '\n';

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
