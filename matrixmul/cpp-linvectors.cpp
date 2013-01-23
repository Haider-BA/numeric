#include <iostream>
#include <cstdlib>
#include <vector>

using std::vector;

void matrixMult(vector<double>& A, vector<double>& B, vector<double>& C, unsigned int N)
{
    unsigned int i, j, k;
    double sum;
    for (i = 0; i<N; i++) {
        for (j = 0; j<N; j++) {
            sum = 0.0;
            for (k = 0; k<N; k++)
                sum += A[k*N+i] * B[j*N+k];
            C[j*N+i] = sum;
        }
    }
}


int main(int argc, char* argv[])
{
    using std::cout;

    unsigned int N, i, j;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else {
        std::cerr << "Sorry, I need matrix width as command line argument\n";
        return 1;
    }

    vector<double> A(N*N);
    vector<double> B(N*N);
    vector<double> C(N*N);

    for (i = 0; i<N; ++i) {
        for (j = 0; j<N; ++j) {
            A[j*N+i] = 2.0;
            B[j*N+i] = (double) N*j + i;
        }
    }

    matrixMult(A, B, C, N);

    return 0;
}
