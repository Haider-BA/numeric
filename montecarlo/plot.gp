set terminal png
set output "performance.png"
set xlabel "Sample points N"
set ylabel "Execution time [s]"
set title "Performane analysis"
set log xy
set grid
plot "performance.dat" u 1:2 title "Plain Monte-Carlo" w lp

set terminal png
set output "error.png"
set xlabel "Sample points N"
set ylabel "Error"
set title "Error analysis"
set log xy
set grid
plot "performance.dat" u 1:3 title "Plain Monte-Carlo" w lp, 1/sqrt(x) w l title "O(1/sqrt(N))"
