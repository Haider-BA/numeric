#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "header.h"
#include "functions.h"
#include "montecarlo.h"

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Number of sample points as input argument
  Lengthtype N;
  if (argc == 1) // If no args are given..
    N = 100; // 100 points are sampled
  else
    N = atol(argv[1]); // Else the specified number

  cout << "Sampling function at " << N << " points.\n";

  // Calculate machine precision
  Floattype eps_machine = 1.0f;
  while (1.0f + eps_machine != 1.0f)
    eps_machine /= 2.0f;

  // Evaluate 3D function A at 10 points in interval [a;b]
  Lengthtype d = 3; // No of dimensions
  std::vector<Floattype> a(d); // Lower limits
  std::vector<Floattype> b(d); // Upper limits
  for (Lengthtype i=0; i<d; ++i) { // Assign equidimensional limits
    a[i] = 0.0f;
    b[i] = M_PI;
  }
  Floattype tic = clock();
  MC mc(functionA, a, b, N);
  mc.plain(); // Plain Monte-Carlo integration
  mc.show();  // Display results
  Floattype t_elapsed = (clock() - tic)/(CLOCKS_PER_SEC);
  cout << "Elapsed time: " << t_elapsed << " s.\n";

  // Append results to performance.dat
  std::ofstream file;
  file.open("performance.dat", std::fstream::app); // Append to file
  file << N << '\t' << t_elapsed << '\t' << mc.error() << '\n';
  file.close();

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
