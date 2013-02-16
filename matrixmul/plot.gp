set terminal pngcairo size 1200,600
set output "performance.png"
set xlabel "Matrix side length"
set ylabel "Execution time [s]"
set title "Matrix multiplication\n".platform.",".cpumodel.", ".threads." threads"
set log xy
set grid
set key outside
set label "http://github.com/anders-dc/numeric/" at screen 0.05,0.02
plot \
         "lua-linarr.dat" title "Lua: Linear arrays" w lp, \
         "lua-arrofarrs.dat" title "Lua: Arrays of arrays" w lp, \
         "luajit-arrofarrs.dat" title "LuaJIT: Arrays of arrays" w lp, \
         "luajit-linarr.dat" title "LuaJIT: Linear arrays" w lp, \
         "c-arrofarrs.dat" title "C: Arrays of arrays" w lp, \
         "c-linarr.dat" title "C: Linear arrays" w lp, \
         "cpp-vectorofvectors.dat" title "C++: Vectors of vectors" w lp, \
         "cpp-linvectors.dat" title "C++: Linear vectors" w lp, \
         "c-omp-arrofarrs.dat" title "C-OpenMP: Arrays of arrays" w lp, \
         "c-omp-linarr.dat" title "C-OpenMP: Linear arrays" w lp, \
         "julia.dat" title "Julia" w lp, \
         "c-gsl-cblas.dat" title "C: GSL CBLAS" w lp, \
         "octave.dat" title "Octave" w lp, \
         "cpp-armadillo.dat" title "C++: Armadillo" w lp, \
         "cpp-eigen.dat" title "C++: Eigen3" w lp

