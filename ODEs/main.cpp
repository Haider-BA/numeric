#include <iomanip>
#include <cstdlib> // Exit function
#include <string.h>
#include <cmath>
#include <vector>

// File I/O
#include <iostream> 
#include <fstream>

using namespace std;

// this function gives the sign
bool sign(double n)
{ return n >= 0; };

void rkdriver(void f(int, double, vector<double>*, vector<double>*),int n, vector<double>* tlist, vector<vector<double> >* ylist, double b, double h, double acc, double eps, int max );

// this function simulates a cannonball
void func1(int n, double x, vector<double>* y, vector<double>* dydx){
  int A = sign((*y)[2]);
  int B = sign((*y)[3]);
  double k = 0.02;
  double g = 9.82;
  (*dydx)[0]=(*y)[2];
  (*dydx)[1]=(*y)[3];
  (*dydx)[2]=sqrt((*y)[2]*(*y)[2]+(*y)[3]*(*y)[3])*-A*k;
  (*dydx)[3]=-g-sqrt((*y)[2]*(*y)[2]+(*y)[3]*(*y)[3])*B*k;
};

int main () {

  int n=4;  // Number of equations
  int max=10000;  // Maximum "iterations"
  double a=0, b=15, h=0.01, acc=0.001, eps=0.001;
  vector<double> tlist(max);  // 
  vector<vector<double> > ylist(max,vector<double>(n)); 
  tlist[0]=a; ylist[0][0]=0; ylist[0][1]=0; ylist[0][2]=100;
  ylist[0][3]=100;
  
  rkdriver(&func1,n,&tlist,&ylist,b,h,acc,eps,max); 
  
  // Printing the output
  int it = 0;
  while(tlist[it]<b) {
    cout << tlist[it] << " ";
    for (int j = 0; j<n;j++) cout << ylist[it][j] << " ";
    cout << endl;
    it++;
  };	
  
};

