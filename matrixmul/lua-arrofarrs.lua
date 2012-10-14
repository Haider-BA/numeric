#!/usr/bin/lua

N = arg[1]

-- Initialize the matrix A with two's,
-- matrix B with random numbers
A = {}
B = {}
C = {}
for i=1,N do
  A[i] = {}
  B[i] = {}
  C[i] = {}
  for j=1,N do
    A[i][j] = 2
    B[i][j] = math.random()
  end
end

-- Multiply matrix A with matrix B,
-- store result in matrix C
for i=1,N do
  for j=1,N do
    sum = 0.0
    for k=1,N do
      sum = sum + A[i][k] * B[k][j]
    end
    C[i][j] = sum
  end
end
