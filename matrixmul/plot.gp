set terminal png size 1200,600
set output "performance.png"
set xlabel "Matrix side length"
set ylabel "Execution time [s]"
set title "Random number generation and matrix multiplication"
set log xy
set grid
set key outside
plot "lua-arrofarrs.dat" title "Lua: Arrays of arrays" w lp, "lua-linarr.dat" title "Lua: Linear arrays" w lp, "luajit-arrofarrs.dat" title "LuaJIT: Arrays of arrays" w lp, "luajit-linarr.dat" title "LuaJIT: Linear arrays" w lp, "c-arrofarrs.dat" title "C: Arrays of arrays" w lp, "c-linarr.dat" title "C: Linear arrays" w lp, "c-omp-arrofarrs.dat" title "C-OpenMP: Arrays of arrays" w lp, "c-omp-linarr.dat" title "C-OpenMP: Linear arrays" w lp, "julia.dat" title "Julia" w lp, "cpp-vectorofvectors.dat" title "C++: Vectors of vectors" w lp, "cpp-linvectors.dat" title "C++: Linear vectors" w lp, "python-numpy.dat" title "Python: Numpy" w lp, "octave.dat" title "Octave" w lp
