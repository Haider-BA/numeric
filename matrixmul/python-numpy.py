#!/usr/bin/env python

import sys
import numpy

if (len(sys.argv) == 2):
  M = int(sys.argv[1])
else:
  print("Sorry, I need a matrix width as input argument!")
  sys.exit(1)

N = M

A = numpy.ones((M,N))*2.0
B = numpy.random.random_sample((M,N))
C = numpy.dot(A,B)  # A*B is element wise on numpy arrays
