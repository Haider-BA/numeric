#include <iostream>
#include <cstdlib>
#include <armadillo>

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

    arma::mat A(N,N);
    arma::mat B(N,N);
    arma::mat C(N,N);

    for (i = 0; i<N; ++i) {
        for (j = 0; j<N; ++j) {
            A(i,j) = 2.0;
            B(i,j) = (double) N*j + i;
        }
    }

    C = A*B;

    return 0;
}
