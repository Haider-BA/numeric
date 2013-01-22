#!/usr/bin/env python
import sys
import numpy

if (len(sys.argv) == 2):
  N = int(sys.argv[1])
else :
  print("Sorry, I need a matrix width as input argument!")
  sys.exit(1)

A = numpy.ones((N,N))*2.0
B = numpy.random.random_sample((N,N))
C = numpy.dot(A,B)
