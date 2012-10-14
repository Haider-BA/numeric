set terminal png	# Set output file format
set output "plot.A.png" # Set output filename
set key top left
set xlabel "x"
set ylabel "y"
set title "Least-squares fit A"
set grid
plot "fit.A.dat" u 1:2 w lp title "LSfit", "data.A.txt" w errorbars title "Data"

set terminal png	# Set output file format
set output "plot.B.png" # Set output filename
set key top left
set xlabel "x"
set ylabel "y"
set title "Least-squares fit B"
set grid
plot "fit.B.dat" u 1:2 w lp title "LSfit", "data.B.txt" w errorbars title "Data"
