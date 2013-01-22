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

  vector<double> A(N*N);
  vector<double> B(N*N);
  vector<double> C(N*N);

  for (i = 0; i<N; ++i) {
    for (j = 0; j<N; ++j) {
      A[j*N+i] = 2.0;
      B[j*N+i] = rand()/RAND_MAX;
    }
  }

  double sum;
  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      sum = 0.0f;
      for (k = 0; k < N; ++k) 
	sum += A[k*N+i] * B[j*N+k];
      C[j*N+i] = sum;
    }
  }

  return 0;
}
