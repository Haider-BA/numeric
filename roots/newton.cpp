#include <functional>
#include <armadillo>
#include "qrfunc.h"

using namespace arma;

// Newton's method
vec newton(std::function<vec(vec)> f, vec x_0, vec dx, double eps)
{
  vec x = x_0;
  int n = x.size();
  mat A(n,n);
  vec y(n);
  vec fx(n);
  vec fy(n);
  vec df(n);
  vec Dx(n);

  do {
    fx = f(x);
    for (int j=0; j<n; ++j) {
      x[j] += dx[j];
      df = f(x) - fx;

      for (int i=0; i<n; ++i)
	A(i,j) = df[i]/dx[j];

      x[j] -= dx[j];
    }

    // Perform QR decomposition
    QR qr(A);
    vec fx_neg = -1.0f*fx;
    Dx = qr.backsub(fx_neg);

    double lambda = 2.0f;
    do {
      lambda /= 2.0f;
      y = x + Dx * lambda;
      fy = f(y);
    } while (norm(fy,2.0f) > (1.0f-lambda/2.0f)*norm(fx,2.0f) && lambda > 0.02f);

    x = y;
    fx = fy;
    std::cerr << "Newton: f(x).norm() = " << norm(fx, 2.0f) << '\n';
  } while (norm(Dx,2.0f) > norm(dx,2.0f) && norm(fx,2.0f) > eps);
  
  // Return solution
  return x;
}

// Newton's method - the user supplies his own derivatives
vec newtonJac(std::function<vec(vec)> f, vec x_0, vec dx, double eps, 
    	      mat (*J)(vec))
{
  vec x = x_0;
  int n = x.size();
  vec y(n);
  vec fx(n);
  vec fy(n);
  vec Dx(n);

  fx = f(x);
    
  do {
    
    // Get Jacobian matrix
    mat Jx = J(x_0);

    // Perform QR decomposition
    QR qr(Jx);
    vec fx_neg = -1.0f*fx;
    Dx = qr.backsub(fx_neg);

    double lambda = 2.0f;
    do {
      lambda /= 2.0f;
      y = x + Dx * lambda;
      fy = f(y);
    } while (norm(fy,2.0f) > (1.0f-lambda/2.0f)*norm(fx,2.0f) && lambda > 0.02f);

    x = y;
    fx = fy;
    std::cerr << "Newton: f(x).norm() = " << norm(fx, 2.0f) << '\n';
  } while (norm(Dx,2.0f) > norm(dx,2.0f) && norm(fx,2.0f) > eps);
  
  // Return solution
  return x;
}
