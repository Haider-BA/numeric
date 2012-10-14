// Make sure header is only included once
#ifndef HEADER_H_
#define HEADER_H_

#include <vector>

// Define whether the program should output values of matrices
const bool verbose = false;

// Choose vector length variable type
typedef int Lengthtype;
 
// Choose floating-point precision
typedef double Floattype;

// File output function prototype
int write_output(const std::vector<Floattype> &a,
    		 const std::vector<Floattype> &b,
		 const char *outfile);

#endif
