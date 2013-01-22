#/usr/bin/octave -q -f --no-window-system

if (nargin == 1)
  N = str2num(argv(){1});
else
  disp("Sorry, I need the matrix size as a command line argument");
  exit(1);
end

A = ones(N,N) * 2.0;
B = reshape(0:N*N-1, N, N);
C = A*B;
