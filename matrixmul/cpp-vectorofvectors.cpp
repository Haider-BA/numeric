#include <iostream>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[])
{
  using std::cout;
  using std::vector;

  int N, i, j, k;

  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    cout << "Sorry, I need matrix width as command line argument\n";
    return 1;
  }

  vector< vector<double> > A(N,vector<double>(N));
  vector< vector<double> > B(N,vector<double>(N));
  vector< vector<double> > C(N,vector<double>(N));
  
  for (i = 0; i<N; ++i) {
    for (j = 0; j<N; ++j) {
      A[i][j] = 2.0;
      B[i][j] = rand()/RAND_MAX;
    }
  }

  double sum;
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      sum = 0.0;
      for (k = 0; k < N; ++k)
	sum = A[k][j] * B[i][k];
      C[i][j] = sum;
    }
  }

  return 0;
}
