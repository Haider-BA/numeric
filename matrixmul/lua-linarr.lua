#!/usr/bin/lua

N = arg[1]

-- Initialize the matrix A with two's,
-- matrix B with random numbers
A = {}
B = {}
for i=1,(N*N) do
  A[i] = 2.0
  B[i] = math.random()
end

-- Multiply matrix A with matrix B,
-- store result in matrix C
C = {}
for i=1,N do
  for j=1,N do
    sum = 0.0
    for k=1,N do
      sum = sum + A[(k-1)*N+i] * B[(j-1)*N+k]
    end
    C[(i-1)*N + j] = sum
  end
end
