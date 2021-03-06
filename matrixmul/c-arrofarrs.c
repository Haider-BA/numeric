#include <stdio.h>
#include <stdlib.h>

void matrixMult(double** A, double** B, double** C, unsigned int N)
{
    unsigned int i, j, k;
    double sum;
#pragma omp parallel for private (j,k,sum) shared(A,B,C,N) default(none)
    for (i = 0; i<N; ++i) {
        for (j = 0; j<N; ++j) {
            sum = 0.0;
            for (k = 0; k<N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}


int main(int argc, char* argv[])
{
    unsigned int i, j, N;
    double** A;
    double** B;
    double** C;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else {
        fprintf(stderr, "Sorry, I need matrix width as command line argument\n");
        return 1;
    }

    A = (double**) malloc(N * sizeof(double*));
    B = (double**) malloc(N * sizeof(double*));
    C = (double**) malloc(N * sizeof(double*));

    for (i = 0; i < N; ++i) {
        A[i] = (double*) malloc(N * sizeof(double));
        B[i] = (double*) malloc(N * sizeof(double));
        C[i] = (double*) malloc(N * sizeof(double));
    }

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            A[i][j] = 2.0;
            B[i][j] = (double) N*j + i;
        }
    }

    matrixMult(A, B, C, N);

    free(A);
    free(B);
    free(C);

    return 0;
}
