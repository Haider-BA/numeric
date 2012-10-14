set terminal png
set output "plotC.png"
set xlabel "x.r"
set ylabel "x.i"
set zlabel "y"
set title "Integration along a complex path"
set grid
splot "funcC.dat" u 1:2:3 t "y.real" w lp, "" u 1:2:4 t "y.imag" w lp

