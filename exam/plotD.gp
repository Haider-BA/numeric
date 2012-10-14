set terminal png
set output "plotD.png"
set xlabel "Precision"
set ylabel "No. of steps"
set title "Number of steps required for a given absolute and relative precision"
set grid
set log xy
plot "funcD.dat" u 1:2 t "rk12" w lp

