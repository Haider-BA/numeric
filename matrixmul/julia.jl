#!/usr/bin/env julia

if (length(ARGS) == 1)
  N = int(ARGS[1])
else
  println("Sorry, I need the matrix width as a command line argument\n")
end

A = ones(N,N)*2.0
B = rand(N,N)
C = A*B
