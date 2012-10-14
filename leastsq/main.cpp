#include <iostream>
#include <cstdio> // For fscanf
#include <armadillo>
#include <vector>
#include "header.h"
#include "lsfit.h"

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Check that a data file is given as an input argument
  if (argc < 2 || argc > 3) {
    cout << "Usage: " << argv[0] << " <input file> [output file]\n"
         << "If 'output file' is not specified, output data "
	 << "will be written to stdout.\n"
         << "Example: " << argv[0] << " data.A.txt\n";
    return 1;
  }

  FILE *fin; // File pointer

  // Check that the input file exists and can be read
  if ((fin = fopen(argv[1], "r")) == NULL) {
    cout << "Error while reading " << argv[1] << '\n';
    return 1;
  }

  // First, count the number of newline characters
  // for preallocation purposes
  Lengthtype n = 0;
  int c;
  while ((c = getc(fin)) != EOF) {
    if (c == '\n')
      ++n;
  }
  fclose(fin);
  cout << "Input file \"" << argv[1] << "\" consists of n=" 
       << n << " data points.\n";

  // Allocate input data structures
  arma::Col<Floattype> x = arma::Col<Floattype> (n);
  arma::Col<Floattype> y = arma::Col<Floattype> (n);
  arma::Col<Floattype> delta_y = arma::Col<Floattype> (n);

  // Read data into memory
  if ((fin = fopen(argv[1], "r")) == NULL) {
    cout << "Error while reading " << argv[1] << '\n';
    return 1;
  }
  float x_tmp, y_tmp, delta_y_tmp;
  for (Lengthtype i=0; i<n; ++i) {
    fscanf(fin, "%f %f %f", &x_tmp, &y_tmp, &delta_y_tmp);
    x(i) = x_tmp;
    y(i) = y_tmp;
    delta_y(i) = delta_y_tmp;
  }
  fclose(fin);

  // Perform least-squares fit with LSfit class
  LSfit lsfit(x, y, delta_y);

  // Evaluate fit at a fine resolution
  const unsigned int res = 100;
  Floattype x_min = x.min();
  cout << "x_min = " << x_min;
  Floattype x_max = x.max();
  cout << ", x_max = " << x_max << '\n';
  std::vector<Floattype> xo (res);
  std::vector<Floattype> yo (res);
  for (unsigned int i=0; i<res; ++i) {
    xo[i] = x_min + (x_max - x_min) * ((Floattype)i/res);
    yo[i] = lsfit.eval(xo[i]);
  }

  // Write to file if specified in as command line arguments
  if (argc == 3) {
    write_output(xo, yo, argv[2]);
  } else {
    for (unsigned int i=0; i<res; ++i) {
      cout << xo[i] << '\t' << yo[i] << '\n';
    }
  }

  
  // Return successfully
  return 0;
}
