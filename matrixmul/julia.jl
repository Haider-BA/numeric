#!/usr/bin/env julia

if (length(ARGS) == 1)
  const N = int(ARGS[1])
else
  println("Sorry, I need the matrix width as a command line argument\n")
end

const A = ones(N, N)*2.0
const B = reshape(0.0:N*N-1, N, N)
C = A*B
