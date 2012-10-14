#!/usr/bin/julia

if (length(ARGS) == 1)
  N = int(ARGS[1])
else
  println("Sorry, I need the matrix width as a command line argument\n")
end

M = N

A = ones(M,N)*2.0
B = rand(M,N)
C = A*B
