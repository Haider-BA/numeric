#ifndef DOWNHILL_SIMPLEX_H_
#define DOWNHILL_SIMPLEX_H_

#include <functional>
#include <vector>
#include <armadillo>
using namespace std;
using namespace arma;

class amoeba {

  public:

    // Constructor
    amoeba(function<double(vec)> fun, vector<vec> simplex);

    // Return lowest simplex position
    vec low();

    // Move amoeba downhill with relevant method
    void downhill(double simplex_size_goal);

    // Move amoeba downhill with relevant method, modified method
    void downhill_mod(double simplex_size_goal);

  private:

    // Number of vertexes
    int d;
    
    // Maxima points of function
    int hi, lo;

    // Vertex points
    vector<vec> p;

    // Functions to be evaluated
    std::function<double(vec)> f;
    
    // Function values at points
    vec value;
    
    // Centroid
    vec p_ce;

    // Centroid from previous step
    vec p_ce_o;

    // Filename of output file

    // Private class functions
    void update();

    // Returns size of the amoeba
    double size();

    // Write amoeba position vertexes to stderr
    void pos();
};

#endif
