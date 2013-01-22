#/usr/bin/octave -q -f --no-window-system

if (nargin == 1)
  M = str2num(argv(){1});
else
  disp("Sorry, I need the matrix size as a command line argument");
  exit(1);
end

N = M;

A = ones(M,N) * 2.0;
B = rand(M,N);
C = A*B;
