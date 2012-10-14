set terminal png
set output "plotA.png"
set xlabel "x.real"
set ylabel "y.real"
set title "Integration along a real path"
set grid
plot "funcA.dat" u 1:3 t "rk12" w lp

