# Define compiler
CC=g++

# Define compiler flags (show all warnings)
CPPFLAGS=-Wall

# Define linker flags
LDFLAGS=

# Define extra libraries to be dynamically linked
LDLIBS+=-larmadillo

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

# Remove file type extension for binary filename
BIN=eigen

# The default "all" depends on A and B

#all: A B
A:
	./eigen 11

#A: plot.A.png

#B: plot.B.png

#plot.%.png: fit.A.dat fit.B.dat data.A.txt data.B.txt
#	gnuplot plotall.gp

#fit.A.dat: $(BIN)
#	./$(BIN) data.A.txt fit.A.dat

#fit.B.dat: $(BIN)
#	./$(BIN) data.B.txt fit.B.dat

$(BIN):	$(OBJ)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN) $(LDLIBS)
	@# Execute program and redirect stdout to file
	@#./$(BIN) > out.txt
	
clean: 
	@# Remove object files
	rm -f $(OBJ)
	@# Remove binary
	rm -f $(BIN)
	@# Remove datafiles and plot
	#rm -f *.dat *.png
edit:
	vim -p Makefile *.cpp *.h *.gp

