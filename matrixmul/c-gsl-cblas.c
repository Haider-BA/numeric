#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_cblas.h>

int main(int argc, char* argv[])
{
    unsigned int i, N;
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
        B[i] = (double)i;
    }

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 
            N, N, N, 1.0, A, N, B, N, 0.0, C, N);

    free(A);
    free(B);
    free(C);

    /* Exit with success */
    return 0;
}
