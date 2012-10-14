#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

// Stepper function
void rkstep(
	void f(int, double, vector<double>*, vector<double>*),
	int n, double t, vector<double>* y, double h, vector<double>* y1, vector<double>* dy)
{
	vector<double> k0(n);
	vector<double> y12(n);
	vector<double> k12(n);
	(*f)(n,t,y,&k0);
	for(int i = 0;i<n;i++) y12[i] = (*y)[i]+k0[i]*h/2;
	(*f)(n,(t+h/2),&y12,&k12);
	for(int i = 0;i<n;i++) (*y1)[i] = (*y)[i]+k12[i]*h;
	for(int i = 0;i<n;i++) (*dy)[i] = (k0[i]-k12[i])*1*(h)/2;
}; 
