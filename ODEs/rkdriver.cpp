#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream> 
#include <fstream>
#include <vector>
using namespace std;

void rkstep(void f(int,double,vector<double>*,vector<double>*),int n, double t,vector<double>* y,double h,vector<double>* y1,vector<double>* dy);

// Main driver function
void rkdriver(void f(int, double, vector<double>*, vector<double>*),int n, vector<double>* tlist, vector<vector<double> >* ylist, double b, double h, double acc, double eps, int max ) {

  int i=0;  //iterator
  double t = (*tlist)[0];
  double a = t; 
  vector<double> dy(n);
  vector<double> y1(n);
  
  while((*tlist)[i]<b) {
    double t=(*tlist)[i];
    vector<double> y=(*ylist)[i];
    if(t+h>b) h=b-t;
    rkstep(f,n,t,&y,h,&y1,&dy);
    double err=0; for(int j=0;j<n;j++)err+=dy[j]*dy[j];
    err=sqrt(err);
    double normy=0; for(int j=0;j<n;j++)normy+=y1[j]*y1[j];
    normy=sqrt(normy);
    double tol=(normy*eps+acc)*sqrt(h/(b-a));

    if(tol>err){ // accept step and go on
      i++;
      if(i>max-1) { 
	cout << "Reached max step \nIncrease max step to go further \n";
	exit(1);
      };

      (*tlist)[i]=t+h;
      
      for(int j=0;j<n;j++) (*ylist)[i][j]=y1[j];
    };

    if(err>0) h = h*pow(tol/err,0.25)*0.95;
    else h = 2*h;
  }//end while				
};
