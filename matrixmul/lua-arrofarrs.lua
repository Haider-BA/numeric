#!/usr/bin/env lua

N = tonumber(arg[1])
if N == nil then error("Sorry, I need matrix width as command line argument") end

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

for i=1,N do
  for j=1,N do
    sum = 0.0
    for k=1,N do
      sum = sum + A[i][k] * B[k][j]
    end
    C[i][j] = sum
  end
end
