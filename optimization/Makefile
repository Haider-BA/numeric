# Define compiler
CC=g++

# Define compiler flags (show all warnings)
CPPFLAGS=-Wall -std=c++0x

# Define linker flags
LDFLAGS=

# Define extra libraries to be dynamically linked
LDLIBS+=-larmadillo -lstdc++

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
#OBJ=$(SRC:.cpp=.o)
OBJ=downhill_simplex.o main.o
OBJB=downhill_simplex.o main.B.o

# Remove file type extension for binary filename
BIN=optim
BINB=optimB

# The default "all" depends on A and B

all: A B


A:	$(BIN)
	@# Run program and write amoeba positions to file
	./$(BIN) 2> amoeba.dat

B:	$(BINB)
	./$(BINB) 2> amoebaB.dat
	
$(BIN):	$(OBJ)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ) -o $(BIN) $(LDLIBS)
	
$(BINB): $(OBJB)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJB) -o $(BINB) $(LDLIBS)

clean: 
	@# Remove object files
	rm -f $(OBJ) $(OBJB)
	@# Remove binaries
	rm -f $(BIN) $(BINB)
	@# Remove datafiles and plot
	#rm -f *.dat *.png
	@# Remove error log
	rm -f amoeba.dat amoebaB.dat
edit:
	vim -p Makefile *.cpp *.h

