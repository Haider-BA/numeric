#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>

int main(int argc, char* argv[])
{
    using std::cout;
    using Eigen::MatrixXd;

    unsigned int N, i, j;

    if (argc == 2) {
        N = atoi(argv[1]);
    } else {
        std::cerr << "Sorry, I need matrix width as command line argument\n";
        return 1;
    }

    MatrixXd A(N,N);
    MatrixXd B(N,N);
    MatrixXd C(N,N);

    for (i = 0; i<N; ++i) {
        for (j = 0; j<N; ++j) {
            A(i,j) = 2.0;
            B(i,j) = (double) N*j + i;
        }
    }

    C = A*B;

    return 0;
}
