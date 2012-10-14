set terminal png
set output "plotB.png"
set xlabel "x.imag"
set ylabel "y.imag"
set title "Integration along an imaginary path"
set grid
plot "funcB.dat" u 2:4 t "rk12" w lp

