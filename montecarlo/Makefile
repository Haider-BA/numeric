# Define compiler
CC=g++

# Define compiler flags (show all warnings)
CPPFLAGS=-Wall
#CPPFLAGS=-std=c++0x

# Define linker flags
LDFLAGS=

# Define extra libraries to be dynamically linked
#LDLIBS+=-larmadillo 
#LDLIBS+=-lstdc++

# Compile optimized code
#CPPFLAGS+=-O2

# Compile debuggable code
#CPPFLAGS+=-g

# Compile profilable code
#CPPFLAGS+=-pg
#LDFLAGS+=-pg

# Define linker
LD=g++

# Filenames of source code
SRC=$(shell ls *.cpp)

# Filenames of object files
OBJ=$(SRC:.cpp=.o)
#OBJ=downhill_simplex.o main.o
#OBJB=downhill_simplex.o main.B.o

# Remove file type extension for binary filename
BIN=mc
#BINB=optimB

# The default "all" depends on A and B

#all: A B

A: performance.png error.png

%.png: performance.dat
	gnuplot plot.gp



performance.dat: $(BIN)
	# Removing old performance data
	rm -f performance.dat
	# Running program and profiling runtime and error
	nice ./$(BIN) 10000 > /dev/null
	nice ./$(BIN) 20000 > /dev/null
	nice ./$(BIN) 50000 > /dev/null
	nice ./$(BIN) 100000 > /dev/null
	nice ./$(BIN) 200000 > /dev/null
	nice ./$(BIN) 500000 > /dev/null
	nice ./$(BIN) 1000000 > /dev/null
	nice ./$(BIN) 2000000 > /dev/null
	nice ./$(BIN) 5000000 > /dev/null


#B:	$(BINB)
#	./$(BINB) 2> amoebaB.dat

test:	$(BIN)
	./$(BIN)
	
$(BIN):	$(OBJ)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN) $(LDLIBS)
	
$(BINB): $(OBJB)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJB) -o $(BINB) $(LDLIBS)

clean: 
	@# Remove object files
	rm -f $(OBJ) 
	@# Remove binaries
	rm -f $(BIN)
	@# Remove datafiles and plot
	rm -f *.dat *.png
edit:
	vim -p Makefile *.cpp *.h *.gp

