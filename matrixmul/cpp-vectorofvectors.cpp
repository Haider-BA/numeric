#include <iostream>
#include <cstdlib>
#include <vector>

using std::vector;

void matrixMult(
        vector< vector<double> >& A,
        vector< vector<double> >& B,
        vector< vector<double> >& C,
        unsigned int N)
{
    unsigned int i, j, k;
    double sum;
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            sum = 0.0;
            for (k = 0; k < N; ++k)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
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

    vector< vector<double> > A(N,vector<double>(N));
    vector< vector<double> > B(N,vector<double>(N));
    vector< vector<double> > C(N,vector<double>(N));

    for (i = 0; i<N; ++i) {
        for (j = 0; j<N; ++j) {
            A[i][j] = 2.0;
            B[i][j] = (double) N*j + i;
        }
    }

    matrixMult(A, B, C, N);

    return 0;
}
