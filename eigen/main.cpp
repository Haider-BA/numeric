#include <iostream>
#include <armadillo>
#include "header.h"
#include "jacobi.h"

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Define matrix size
  Lengthtype msize = 6;
  if (argc == 2) {
    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
      cout << "Usage: " << argv[0] << " [matrix size]\n"
	   << "If matrix size is not specified, "
	   << "the matrix width and length will be "
	   << msize << ".\n";
      return 1;
    } 
    msize = atoi(argv[1]); // Use specified matrix size
  }

  // Calculate machine precision
  Floattype eps = 1.0f;
  while (1.0f + eps != 1.0f)
    eps /= 2.0f;
  //cout << "Machine precision of '" << typeid(eps).name() 
  //     << "' type is: eps = " << eps << '\n';

  Floattype checksum;
  // Generate input matrix A, which is symmetric
  cout << "\n\033[1;33m--- Input data check ---\033[0m\n";
  arma::Mat<Floattype> A = symmatu(arma::randu< arma::Mat<Floattype> > (msize, msize));
  checksum = arma::sum(arma::sum(A - A.t()));
  cout << "Symmetry check: A = A^T: ";
  check(checksum < eps);
  if (verbose == true) {
    A.print("Original matrix:");
  }

  // Perform Jacobi diagonalization of matrix A
  Jacobi Diag = Jacobi(A);

  cout << "\n\033[1;33m--- Diagonalization check ---\033[0m\n";
  if (verbose == true)
    Diag.trans().print("Transformed matrix (At):");
  cout << "Check: V V^T = 1: \t";
  checksum = arma::sum(arma::sum(Diag.eigenvectors().t() * Diag.eigenvectors()));
  check(fabs(checksum - (Floattype)msize) < eps*msize*msize);
  if (verbose == true) {
    Diag.eigenvalues().print("Eigenvalues (e):");
    Diag.eigenvectors().print("Eigenvectors (V):");
    Diag.eigenvectors().t().print("V^T");
    (Diag.eigenvectors() * Diag.eigenvectors().t()).print("V V^T");
    (Diag.eigenvectors().t() * A * Diag.eigenvectors()).print("V^T A V");
    (Diag.eigenvectors().t() * Diag.trans() * Diag.eigenvectors()).print("V^T At V");
  }

  // Armadillo implementation
  arma::Mat<Floattype> V_a (msize, msize);
  arma::Col<Floattype> e_a (msize);
  arma::eig_sym(e_a, V_a, A);
  if (verbose == true) {
    e_a.print("Armadillo eigenvalues:");
    V_a.print("Armadillo eigenvectors:");
  }
  cout << "\n\033[1;33m--- Armadillo comparison ---\033[0m\n";
  checksum = arma::sum(arma::sum(V_a - Diag.eigenvectors()));
  cout << "Eigenvectors identical:\t";
  check(checksum < eps*msize*msize*2);
  checksum = arma::sum(arma::sum(e_a - Diag.eigenvalues()));
  cout << "Eigenvalues identical: \t";
  check(checksum < eps*msize*2);


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
