# vim: set tw=80:noautoindent

For Jacobi exercise: Use atan2().

11-4: Introduction
#####
Deadline for exercises: ~2 weeks after assignment

All exercises must be done on Lifa:
  lifa.phys.au.dk
  Ethernet: vlifa01 or vlifa02
You need RSA keys to login from outside net.
Login from inside: NFIT credentials.

Alternative server: molveno
Dedicated for numerical course.

Lifa will have approx. 5 year old software, molveno is updated.

All phys.au.dk servers have NFS shared home folders.

Dmitri answers:
http://www.phys.au.dk/~fedorov/numeric/

Bash: Last command starting with e.g. 'v': !v

Exercises are weighted 75% and the exam 25%. You do need to complete at least
51% of the exam. 

02: >51%
4:  >60%
7:  >80%
10: >90%
12: 100%

16-4: Interpolation
####
Makefiles_:
For all project, use makefiles, the project is evaluated by `make clean; make`.

General structure of Makefile:
 Definitions of variables
 all:       my_target
 Target(s): Dependenc(y,ies)
  <-tab->   Command(s)

Strings are denoted without decoration, variables as $(VAR).
To use the CC system linker to link C++ objects, add libraries:
  LDLIBS += -lstdc++
If you use e.g. g++ as the linker, the above command is not needed.

If an object file is required as a dependency, the Makefile will issue a CC
command, compiling the source code file with the same basename. `make -p | less` 
will show all build rules, even build in.

Interpolation_:
When you have a discrete set of datapoints, and you want a function that 
describes the points.

If a function is analytical and continuous, and an infinitely large table of
datapoints in an interval, the complete analytical function can be found from a
taylor-series of _all_ derivatives in the interval.

k-Polynomial: k+1 unknowns (variables). High polynomials tend to oscillate.

Cubic interpolation: The interval between points can be described by a function
of three polynomials.

Spline interpolation: Also made of polynomials. First order spline (a0+x*a1),
simply connects the data points linearly. The splines for each inter-datapoint
interval must have the same values at the data points. The derivates are
discontinuous.

Solving linear splines:
Datapoints: {x_i,y_i}, i = 1,...,n
Splines (n-1): S_i(x) = a_i + b_i (x - x_i)
               S_i(x_i) = y_i                   (n equations)
               S_i(x_{i+1}) = S_{i+1}(x_i)      (n-2 equations (inner points))
Unkowns: a,b: 2n-2 variables. Solution:
  => a_i = y_i
     S_i(x) = y_i + b_i (x-x_i)
     S_i(x_{i+1}) = y_i + b_i (x_{i+1} - x_i)
  => b_i = (y_{i+1} - y_i) / (x_{i+1} - x_i)

Start of by searching which interval x is located in. Optionally, remember the
interval, as the next value will probably lie in the same interval.

Binary search: Is x between x_1 and x_n? If not, error: Extrapolation.
Continuously divide the interval into two, and find out if the x is in the
larger or smaller part.
DO A BINARY SEARCH.

Second order spline:
  S_i(x) = a_i + b_i(x-x_i) + c_i(x-x_i)^2
  Unknowns: 3(n-1) = 3*n-3
  Equations: 3*n-4
  The derivatives are also continuous.
  
Solution:
  a_i = y_i
  \delta x = (x-x_i)
  y_i + b_i \delta x_i + c_i \delta x_i^2 = y_{i+1}
  b_i + 2 c_i \delta x_i = b_{i+1}
Suppose you know b_i, you can find c_i. From that you can find b_{i+1}, and in
turn, c_{i+1}. Through recursion you find all unknowns by stepping forward.
The backwards solution can be found from the last data-point (y_n) by solving 
the two equations with c_{n-1} and b_{n-1} as the two unkowns.

Symmetry can be used as an extra condition.


18-4: 
##############
Interpolation exercise, plotting optionally in gnuplot, or graph (from
plotutils):
  graph -T png points.dat > plot.png
In makefile, example:
  plot.png: points.dat
        graph --display-type png $^ > $@
Each dataset in points.dat needs a header, e.g. # m=1, S=0

lspline.cc: Linear spline
qspline.cc: Quadratic spline
cspline.cc: Cubic spline

Linear spline:
  S(x) = S_i(x) it x in [x_i,x_(i+1)]
  S_i(x) = a_i + b_i (x-x_i)
  S_i(x) = y_i + (\delta y_i)/(\delta x_i) (x-x_i)
  S_i(x_i) = y_i
  \delta y_i = y_(i+1) - y_i
  S_i (x_(i+1)) = y_(i+1)

In C++:
  std::vector<double> x,y,p;
Maybe typecasting? Could be fun.

Procedural programming:
--
  struct lspline {
        int n;
        vector<double> x,y,p;
  };

Make a function:
  struct lspline* construct_lspline(vector<double>&x, vector<double>&y)
  double evaluate_lspline(struct lspline * asdf, double z)
  free_lspline();

Object-oriented programming:
--
If you want to take the structural approach, you keep the functions and
structures seperate. If you take a OO approach, put the functions inside the
structure (or class):
  struct lspline {
        int n;
        vector<double> x,y,p;
        lspline(...,..); // Constructor, same name as struct
        double eval(double z);
  };
  struct lspline ms(x,y);
  ms.eval(z);

See Dmitri's cubic spline example which uses OO.

Functional programming (in C++11), compile with -std=c++0x:
--
The functions can return functions:

  #include <functional>
  using namespace std;

  function<double(double)> flspline (vector<double>&x, vector<double>&y);

  auto my_spline = flspline(x,y);
  my_spline(5,0);


System of linear equations:
-------
A*x = b

A_i,j x_j = b_i

Solve by finding A^(-1): x = A^(-1) * b
Numerically, you calculate the inverse by solving Ax=b.
We will assume that the matrixes are not singular.

  Turn the system into a triangular form.
  The main diagonal is non-zero, all lower values are 0, and upper values are
  denoted T_nn.
  T_nn * x_n = b_n => x_n = 1/T_nn * b_nn
  T_(n-1,n-1) x_(n-1) + T_(n-1,n) x_n = b_(n-1)
  T_ii x_i + sum^n_(j=i+1) T_(i,j) x_j = b_i
  x_i = 1/T_ii (b_i - sum^n_(j=i+1) T_ij, x_j)

The simplest triangulation is by Gauss elimination. Numerically, the simplest
method is LU decomposition (Lower Upper). 
  A = LU, where L=lower triangle, U=upper triangle.
  n^2 equations.
  L and U contain "(n^2 - n)/2 + n" elements.
  L+U = n^2/2 + n/2 = (n(n+1))/2

  The diagonals in L are all equal to 1: L_ii = 1.
  See Dolittle algorithm in the lecture notes, which with the LU system is the
  most used, and fastest method for solving a linear equation.
  
  Ax = b
  LUx = b, Ux=y

Another method: QR decomposition: R=Right triangle (equal to U).
  A = QR
  Q^T Q = 1 (orthogonal)

  Ax = b
  QRx = b
  Rx = Q^T b

  Gram-Schmidt (spelling?) orthogonalization:
  Consider the columns of your matrix A. Normalize them. Orthogonalize all other
  columns to the first column.

  Normalizing the column: ||a_1|| = sqrt(a_1 dot a_i)
  Orthoginalize columns: a_2/||a_1|| -> q_1

  Numerically:
    for j=2 to m:
      a_j - dot(dot(q_1,a_j),q_1) -> a_j
      a_2 -> a_2/||a_2|| = q_2

Find inverse matrix:
  A A^-1 = diag(1)



30-4: Diagonalization
#########################

Runtime comparison: Do a number of comparisons with different matrix sizes
etc.numeric-2012

Easiest way to diagonalize a matrix: Orthogonal transformation
  A -> Q^T A Q = D
Q matrix can be built with e.g. QR decomposition. Rotation: Computers to cyclic
sweep, which is faster than the classic rotation.
Cyclic: Zero all elements above the diagonal, and do your rotations until the
matrix is diagonal. The matrix is converged if none of the eigenvalues have
changed more than machine precision. You will destroy the upper half plus the
diagonal. If you store the diagonal in another vector, you can preserve the
matrix values.
In the beginning, you look for the largest element in each row, and create an
index which is a column that keeps the numbers of the largest elements.
With an index, you can perform the operation fast. You have to update the index
after each operation. 

For very large matrixes, > system memory:
Krylov subspace methods: You use only a subspace of the whole space, and
diagonalize the matrix in the subspace.


02-5: Ordinary Differential Equations (ODEs)
############################################

  dy/dx = f(x,y)

Usually coupled equations:
  dy_1/dx = f_1(x,y_1,y_2)
  dy_2/dx = f_1(x,y_1,y_2)
  [y_1, ..., y_n] = y
  [f_1(x,y), ..., f_n(x,y) = f(x,y)
  y' = f(x,y)
x is usually time. If f has the above form, it is a ODE.
Sine function:
  y'' = -y
In this form, it is not a ODE, because it has a second derivative.
You can redifine it to be an ODE:
  => y  = u_1   ->   u'_1 = u_2
     y' = u_2   ->   u'_2 = -u_1

Solving ODEs with a starting condition:
  y' = f(x,y)
  y(x_0) = y_0
  a->b  (Shape of the function in the interval)
You can calculate the derivative at (x_0,y_0). You then make a step towards
x_0+h, and apply Euler's method:
  y' \approx (\delta y)/(\delta x) = (y(x_0+h) - y_0)/h
  y(x_0+h) \approx y(x_0) + h*f(x_0,y_0)
  y(x) = y_0 + y'_0(x-x0) + 1/(2!) y''_0(x_0)(x-x_0)^2 + ...    (Taylor exp.)
You can find the higher-order terms by sampling points around (x_0,y_0).
Estimate the new derivative half a step towards h, which is used for the first
point. You sample your function, and fit a polynomial. Higher order polynomiums
tend to oscillate.
When solving ODE's the many sampled points create a tabulated function. If you
want to do something further with the function, you interpolate the points by
e.g. splines.
Only three steps are needed if the equation is a parabola. Other functions are
called multi-step methods. You do not want to go to high in the
Taylor-expansion, as there lies a danger with the higher order terms
oscillating.
If the function is changing fast inside an interval, the step size h needs to be
small. This is done by a driver.
The Runge-kutta is single step, and the most widely used.

Absolute accuracy (delta) vs. relative accuracy (epsilon) can behave
significantly differently when the machine precision is reached.
The user usually specifies both, and the accuracy is satisfied, when one of the
conditions are met (the tolerance, tau).
  tau = delta + epsilon*||y|| 

Stepper: Must return y(x+h), e (error estimate).
Driver: x->x+h. If e is smaller than tau, it accepts the step.
The driver finds the size of the next h:
  h_next = h(tau/e)^power * safety
  power = 0.25
  safety = 0.95
  The driver thus increases the step size if the error was low relative to the
  tolerance, and vice-versa.

  Runge principle for determining the error:
    e = C*h^(p+1)
  You first do a full h step, then two h/2 steps.
    2*c*(h/2)^(p+1) = c * (h^(p+1))/(2^p)
  For the error, you calculate y_1 from full step, and then y_1 from two half steps:
    e = ||y_1(full step) - y_1(2 half steps)||
  You can also instead use RK1 and RK2, and evaluate the difference between the
  two for the same step.

The effectiveness of the driver and stepper is determined by how many times you
call the right-hand side of the ODEs. 

Save the x and y values in a C++ vector, and add dynamically using the
push_back() function.


07-5: Nonlinear equations and optimization
#####
Pipe stdin to program:
  cat input.txt | ./my_prog
Redirect stdout to file:
  ./my_prog > out.txt
Redirect stderr to file:
  ./my_prog 2> err.txt

Jacobian matrix: Filled with partial derivatives. Used for linearizing the
problem. f(x+\delta x) \approx f + J \delta x

Machine precision: double: 2e-16. It is the largest number where 1 + eps = 1.

Quasi-Newton methods: Might be exam exercise.


14-5: Numerical integration
#####
Examination problem: FFT or Multiprocessing

Functions for calculating:
  \int_a^b f(x) dx

Often not possible analytically, thus numerical aproach. Most differential
operations are possible analytically. 

Riemann integral: Numerical approximation.
You divide the interval into subintervals (t_1, ..., t_n).
Riemann sum:
  S_n = \sum_{i=1}^n f(x_i) \Delta x_i
Approaching the integral as the interval approaches 0.0. The geometric
interpretation corresponds to rectangles with height f(x_i) and width \Delta
x_i. The function passes trough the middle of the top side of the rectangles.
The integral exists also for discontinuous functions.

Rectangle method: Stable, does no assumptions
    \int_a^b f(x) dx \approx \sum_{i=1}^n f(x_i) \Delta x_i
Trapezum method: 
  Instead of one point inside the interval, two points are calculated, and the
  average is used.
     \int_a^b f(x) dx \approx \sum_{i=1}^n (f(x_{i+1} )+ f(x_i))/2 * \Delta x_i
Adaptive methods:
  The \Delta x_i is adjusted to how flat the function is in an interval.
  As few points as possible are used. 
Polynomial functions:
  Analytical solutions exist. Taylor series expansion. w_i: Weight.
    \sum_{i=1}^n w_i f(x_i) => \int_a^b f(x) dx
    `---- quadrature -----`
  n functions: {\phi_1(x),...,\phi_n(x)}
  Often the polynomials are chosen: {1,x,x^2,...,x^{n-1}}
    \sum_{i=1}^n w_i \phi_k(x_i) = I_k
    I_k =  \int_a^b \phi_k (x) dx
Gauss methods:
  Also use the quadratures as tuning parameters, as the polynomial method.
  w_i,x_i as tuning parameters: 2*n tuning parameters.
    \int_a^b f(x) w(x) dx
  Functions like 1/sqrt(x) or sqrt(x) are handled through the weight function.
  See the lecture notes for details. Both nodes and weights are adjusted.
  
The method to use is dependent on the problem at hand.



