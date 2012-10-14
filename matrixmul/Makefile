# Compare speed of different programming languages
# in a matrix multiplication algorithm: AB=C.
# A is uniform with the cell values '2', B should contain
# pseudorandom numbers.
# Initialization of A, B and C in the same loop is allowed,
# but the multiplication should be done in a separate loop.
# Matrix dimensions are specified as a command line argument.

MATRIXDIMS_SLOW = 100 200 400 800 1600  
MATRIXDIMS = $(MATRIXDIMS_SLOW) 3200
PREFIXCMD = nice \gtime -ao

CC=gcc
CXX=g++
CFLAGS=-Wall -O3
CXXFLAGS=-Wall -O3

performance.png: plot.gp lua-arrofarrs.dat lua-linarr.dat luajit-arrofarrs.dat luajit-linarr.dat c-arrofarrs.dat c-linarr.dat c-omp-arrofarrs.dat c-omp-linarr.dat julia.dat cpp-vectorofvectors.dat cpp-linvectors.dat python-numpy.dat octave.dat
	gnuplot plot.gp

# Lua: Matrices as arrays of arrays
lua-arrofarrs.dat: lua-arrofarrs.lua
	# lua-arrofars.lua 
	@rm -f $@
	@for dims in $(MATRIXDIMS_SLOW); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" lua $< $$dims; \
	  echo $$dims; \
	done

# Lua: Matrices as linear arrays
lua-linarr.dat: lua-linarr.lua
	# lua-linarr.lua
	@rm -f $@
	@for dims in $(MATRIXDIMS_SLOW); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" lua $< $$dims; \
	  echo $$dims; \
	done

# LuaJIT: Matrices as arrays of arrays
luajit-arrofarrs.dat: lua-arrofarrs.lua
	# luajit-arrofars.lua
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" luajit $< $$dims; \
	  echo $$dims; \
	done

# LuaJIT: Matrices as linear arrays
luajit-linarr.dat: lua-linarr.lua
	# LuaJIT lua-linarr.lua
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" luajit $< $$dims; \
	  echo $$dims; \
	done

# C: Array of arrays
c-arrofarrs.dat: c-arrofarrs
	# c-arrofarrs
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

# C: Matrices as linear arrays
c-linarr.dat: c-linarr
	# c-linarr
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

# C: Array of arrays, OpenMP
c-omp-arrofarrs.dat: c-omp-arrofarrs
	# c-omp-arrofarrs
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

# C: Matrices as linear arrays, OpenMP
c-omp-linarr.dat: c-omp-linarr
	# c-omp-linarr
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

c-omp-arrofarrs: c-arrofarrs.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

c-omp-linarr: c-linarr.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

# Julia, native arrays
julia.dat: julia.jl
	# julia.jl
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" julia $< $$dims; \
	  echo $$dims; \
	done

# C++: Vector of vectors
cpp-vectorofvectors.dat: cpp-vectorofvectors
	# cpp-vectorofvectors
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

# C++: Linear vectors
cpp-linvectors.dat: cpp-linvectors
	# cpp-linvectors
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" ./$< $$dims; \
	  echo $$dims; \
	done

# Python: Numpy module
python-numpy.dat: python-numpy.py
	# python-numpy.py
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" python $< $$dims; \
	  echo $$dims; \
	done

# Octave
octave.dat: octave.m
	# octave.m
	@rm -f $@
	@for dims in $(MATRIXDIMS); do \
	  $(PREFIXCMD) $@ -f "$$dims %e" octave -qf $< $$dims; \
	  echo $$dims; \
	done

clean:
	rm -f *.o
	rm -f *.dat
	rm -f *.png

edit:
	vim -p Makefile plot.gp