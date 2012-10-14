#include <iostream>
#include <vector>
#include <cstdlib> // rand is here

int main(int argc, char* argv[])
{
  using std::cout;
  using std::vector;

  int M, N, i, j, k;

  // Read input argument as matrix height
  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    cout << "Sorry, I need matrix width as command line argument\n";
    return 1;
  }

  // Width equal to height
  M = N; 

  vector< vector<double> > A(M,vector<double>(M));
  vector< vector<double> > B(M,vector<double>(M));
  vector< vector<double> > C(M,vector<double>(M));
  
  // Fill matrices A and B with values
  for (i = 0; i<N; ++i) {
    for (j = 0; j<M; ++j) {
      A[i][j] = 2.0;
      // We want a random value between 0 and 1
      B[i][j] = rand()/RAND_MAX;
    }
  }

  double sum;
  // Perform matrix multiplication
  for (i = 0; i < N; ++i) {
    for (j = 0; j < M; ++j) {
      sum = 0.0;
      for (k = 0; k < M; ++k)
	sum = A[k][j] * B[i][k];
      C[i][j] = sum;
    }
  }

  // Exit with success
  return 0;
}
