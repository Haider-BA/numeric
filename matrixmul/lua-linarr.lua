#!/usr/bin/env lua

N = tonumber(arg[1])
if N == nil then error("Sorry, I need matrix width as command line argument") end

A = {}
B = {}
for i=1,(N*N) do
  A[i] = 2.0
  B[i] = i-1
end

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
