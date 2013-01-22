#include <stdlib.h>
#include <stdio.h>

void matrixMult(double* A, double* B, double* C, int N)
{
  int i, j, k;
  double sum;
#pragma omp parallel for private (j,k,sum)
  for (i = 0; i<N; i++) {
    for (j = 0; j<N; j++) {
      sum = 0.0f;
      for (k = 0; k<N; k++) {
	sum += A[k*N+i] * B[j*N+k];
      }
      C[j*N+i] = sum;
    }
  }
}


int main(int argc, char* argv[])
{
  int i, N;
  double* A;
  double* B;
  double* C;

  if (argc == 2) {
    N = atoi(argv[1]);
  } else {
    printf("Sorry, I need matrix width as command line argument\n");
    return 1;
  }

  A = (double*) malloc(N * N * sizeof(double*));
  B = (double*) malloc(N * N * sizeof(double*));
  C = (double*) malloc(N * N * sizeof(double*));

  for (i = 0; i < N*N; i++) {
    A[i] = 2.0;
    B[i] = rand()/RAND_MAX;
  }

  matrixMult(A, B, C, N);

  free(A);
  free(B);
  free(C);

  /* Exit with success */
  return 0;
}
