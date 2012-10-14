set terminal png	# Set output file format
set output "plot.png" # Set output filename
set key top left
set xlabel "Matrix width and height"
set ylabel "Execution time [s]"
set title "Performance comparison of QR decomposition"
set log xy
set grid
plot "performance.dat" u 1:2 title "Homegrown" w lp, "performance.dat" u 1:3 title "Armadillo" w lp
