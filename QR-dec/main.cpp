#include <iostream>
#include <fstream>
#include <ctime>
#include <armadillo>
#include "header.h"
#include "qrfunc.h"

int main(int argc, char* argv[])
{
  // Namespace declarations
  using std::cout;

  // Timer variables
  double tic1, toc1, tic2, toc2;

  // Create 2D matrices from Armadillo templates
  Lengthtype width;
  if (argc == 1) // If no command line argument is given...
    width = 4;   // Matrices are 4x4.
  else
    width = atoi(argv[1]); // Else the specified size

  const Lengthtype height = width;
  cout << "\nInitializing " << width << " by " << height << " matrices.\n";
  arma::mat A = arma::randu<arma::mat>(width, height);

  // QR decomposition is performed upon initialization of QR class
  tic1 = clock();  // Start clock1
  QR qr(A);
  toc1 = clock();  // Stop clock1
  
  //// QR decomposition check
  cout << "\n\033[1;33m--- QR decomposition check ---\033[0m\n";
  if (verbose == true) {
    // Display values to stdout
    qr.A.print("Original A:");
  }

  // Check QR decomposition
  if (verbose == true) {
    qr.Q.print("Q, after QR dec:");
    qr.Q.t().print("Q^T:");
    qr.R.print("R, after QR dec:");
    cout << '\n';
  }

  // Check that matrix is orthogonal
  arma::mat QTQ = qr.Q.t()*qr.Q;
  Floattype checksum = arma::sum(arma::sum(QTQ));
  if (verbose == true) {
    QTQ.print("Q^T Q:");
    cout << "sum = " << checksum << '\n';
  }
  cout << "Check: Q^T Q = 1: \t";
  check(checksum-(Floattype)height < 1e-12f);

  cout << "Check: QR = A by ||QR-A|| = 0: ";
  checksum = sum(sum((qr.Q*qr.R)-qr.A));
  check(checksum < 1e-12f);


  //// Solving linear equations
  cout << "\n\033[1;33m--- Solving linear equations: Ax=b ---\033[0m\n";
  cout << "Solving QRx=b.\n";
  arma::vec b = arma::randu<arma::vec>(qr.size());
  
  // Perform back-substitution of QR system
  if (verbose == true) {
    b.print("Vector b:");
  }

  arma::vec x = qr.backsub(b);

  if (verbose == true) {
    x.print("Solution, x:");
  }

  cout << "Check: Ax = b by |Ax-b| = 0: ";
  checksum = arma::sum(arma::sum(qr.A*x - b));
  check(checksum < 1e-12f);

  //// Calculating the determinant
  cout << "\n\033[1;33m--- Determinant of A ---\033[0m\n";
  cout << "|det(A)| = " << qr.det() << '\n';

  //// Calculating the inverse
  cout << "\n\033[1;33m--- Inverse of A ---\033[0m\n";
  arma::mat Ainv = qr.inverse();
  if (verbose == true)
    Ainv.print("A^(-1):");
  cout << "Check: (A^(-1))^(-1) = A: ";
  QR qrinv(Ainv);
  arma::mat Ainvinv = qrinv.inverse();
  bool equal = true; // Elementwise comparison of values
  for (Lengthtype i=0; i<width; ++i) {
    for (Lengthtype j=0; j<height; ++j) {
      if (fabs(A(i,j)-Ainvinv(i,j)) > 1e12f) {
	equal = false;
	cout << "At (" << i << "," << j << ") = "
	     << "A = " << A(i,j) 
	     << ", (A^(-1))^(-1) = " << Ainvinv(i,j) << '\n';
      }
    }
  }
  check(equal);

  //// Use the Armadillo built-in QR decomposition
  tic2 = clock(); // Start clock2
  arma::mat Q, R;
  arma::qr(Q, R, A);
  toc2 = clock(); // Stop clock2

  //// Statistics
  // Print resulting time of homegrown function and Armadillo function
  cout << "\n\033[1;33m--- Performance comparison ---\033[0m\n";
  double t1 = (toc1 - tic1)/(CLOCKS_PER_SEC);
  double t2 = (toc2 - tic2)/(CLOCKS_PER_SEC);
  cout << "Homegrown implementation: \t" << t1 << " s \n"
       << "Armadillo implementation: \t" << t2 << " s \n";

  cout << "Benchmarking performance across a range of sizes...\n";

  // Write results to file
  std::ofstream outstream;
  // Open outfile for write
  outstream.open("performance.dat");
  double homegrown_time, armadillo_time;

  // Define sizes
  Lengthtype dims[] = {32, 64, 128, 256, 512, 1024, 2048};
  Lengthtype ndims = sizeof(dims)/sizeof(int); // Number of entries in dims

  // Loop through sizes and record performance
  for (Lengthtype i=0; i<ndims; ++i) {
    cout << " " << dims[i] << std::flush;
    // Generate input matrix
    arma::mat An = arma::randu<arma::mat>(dims[i],dims[i]);
    
    // Homegrown implementation
    tic1 = clock();
    QR qrn = QR(An);
    toc1 = clock();

    // Armadillo implementation
    tic2 = clock();
    arma::mat Qn, Rn;
    arma::qr(Qn, Rn, An);
    toc2 = clock();

    // Record time spent
    homegrown_time = (toc1 - tic1)/(CLOCKS_PER_SEC);
    armadillo_time = (toc2 - tic2)/(CLOCKS_PER_SEC);

    // Write time to file in three columns
    outstream << dims[i] << '\t' << homegrown_time << '\t' << armadillo_time << '\n';
  }
  
  cout << '\n';
  // Close file
  outstream.close();

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
