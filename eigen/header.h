// Make sure header is only included once
#ifndef HEADER_H_
#define HEADER_H_

// Define whether the program should output values of matrices
const bool verbose = false;
//const bool verbose = true;

// Choose vector length variable type
typedef int Lengthtype;
 
// Choose floating-point precision
//typedef float Floattype;
typedef double Floattype;
//typedef long double Floattype;
 
// Prototype for checking function
void check(const bool statement);

#endif
