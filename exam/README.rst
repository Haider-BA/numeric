============================================
README: ODE integration with complex numbers
============================================
Exam exercise for *Numerical Methods* by Anders D. Christensen (mail_)

File description
----------------
- ``Makefile``: Description for GNU Make, handles compilation and execution.
- ``README.rst`` (this file): Description of numeric implementation and usage.
  Written with reStructuredText syntax.
- ``check.cpp``: Function for displaying the state of a condition to stdout.
- ``check.h``: Prototype for the check-function.
- ``functions.h``: Input functions to be evaluated.
- ``mainA.cpp``: Main source code file for part A.
- ``ode.cpp``: Constructor and functions for the ODE class, including Runge-Kutta
  stepper and driver.
- ``ode.h``: Header file with the ODE class. This file must be included in all 
  programs that want to utilize the ODE functionality.
- ``plot.gp``: Script for plotting all graphs with Gnuplot.
- ``typedefs.h``: Header file containing definitions of two main types,
  ``Inttype``, a whole-number type, and ``Floattype``, a floating point number
  type. The type definitions can be changed to different lengths and precisions.
  The program can be compiled for verbose output by changing the ``verbose``
  variable.
- ``vector_arithmetic.h``: Operator overloading functions for the ``std::vector``
  class.

Problem descriptions
--------------------
The four generated executables each demonstrate the ODE solvers functionality by
performing the following tasks. The results consist of the console output and
the corresponding plot with filename ``plot<Character>.png``.
- *A*: Construct an ODE solver that can handle functions with complex values.
Demonstrate that it solves the real component correctly, by stepping along
a path in the real range.
- *B*: Demonstrate that the ODE solver can solve the imaginary component by
stepping along a path in the imaginary range.
- *C*: Demonstrate the solution of a set of complex equations by stepping
through the complex plane.
- *D*: For an integration path in the complex plane, visualize how the
requirements of absolute- and relative precision are related to the number of
integration steps, for a given floating point precision.

Implementation
--------------
This exercise was written in object-oriented C++ for easy reuse. For
portability, all included classes are from the standard template library.

The necessary ``std::vector`` arithmetic operations where overloaded to support
element-wise operations, such as vector-scalar multiplication, vector-vector
addition, etc. This approach was preferred over using ``std::valarray``, since it
is not dynamically expandable.

When creating a new ODE object, the user specifies the end-points of the linear
range, where the specified system of ordinary differential equations with
complex values will be solved. The range end-points are complex numbers
themselves, and the user can thus specify whether the integrator steps through a
range of real values, imaginary values, or both components in the complex plane.

The solver steps through the specified range by an adaptive step size, which is
also a complex number. The user specifies the fraction of the range to be used
as a start value for the step. The default value is 0.01.

The ODE class contains functions for writing the ODE solution to stdout
(``ODE::print``) or to a text file (``ODE::write``). The output format is the
following; the first column is the real part of x, second column the imaginary 
part.  The subsequent columns do in turn consist of real- and imaginary parts of 
the variables in the ODE.

The program requires a modern C++ compiler, GNU Make and Gnuplot. It has been
tested with GCC, Clang and llvm.

Compiliation and execution
--------------------------
To make and execute the program, go to the root folder and type `make`. This
will compile and execute the programs for part A-D, and plot output graphs. If
desired, individual parts can be compiled and executed using `make <Character>`.

To view the source code in a browser with vim's syntax highlighting, type `make
html`, and view the files in the `html` folder. The generation of HTML files
requires a newer vim for the source code files, and Docutils for the readme.

All output and objects can be removed using `make clean`.



.. _mail: mailto:adc@geo.au.dk

#vim: set tw=80
