# Define compiler
#CXX=g++

# Define compiler flags (show all warnings)
CXXFLAGS=-Wall
#CXXFLAGS=-std=c++0x

# Define linker flags
#LDFLAGS=-fopenmp

# Compile optimized code
CXXFLAGS+=-O2

# Compile debuggable code
#CXXFLAGS+=-g

# Compile profilable code
#CXXFLAGS+=-pg
#LDFLAGS+=-pg

# Define linker
LD=g++

# All source code files
SRC=$(shell ls *.cpp)


# Filenames of source code
SHARED_SRC=ode.cpp check.cpp
SHARED_HEADERS=typedefs.h ode.h functions.h check.h
SRC_A=mainA.cpp $(SHARED_SRC)
HEAD_A=$(SHARED_HEADERS)
SRC_B=mainB.cpp $(SHARED_SRC)
HEAD_B=$(SHARED_HEADERS)
SRC_C=mainC.cpp $(SHARED_SRC)
HEAD_C=$(SHARED_HEADERS)
SRC_D=mainD.cpp $(SHARED_SRC)
HEAD_D=$(SHARED_HEADERS)

# Filenames of object files
OBJ_A=$(SRC_A:.cpp=.o)
OBJ_B=$(SRC_B:.cpp=.o)
OBJ_C=$(SRC_C:.cpp=.o)
OBJ_D=$(SRC_D:.cpp=.o)

# Remove file type extension for binary filename
BIN_A=odeA
BIN_B=odeB
BIN_C=odeC
BIN_D=odeD

# Define editor and options for `make edit`
EDITOR=vim -p


# The default "all" depends on A and B
all: A B C D

A:	plotA.png

B:	plotB.png

C:	plotC.png

D:	plotD.png

plotA.png: funcA.dat plotA.gp
	# Gnuplot: plotA.png
	@gnuplot plotA.gp

plotB.png: funcB.dat plotB.gp
	# Gnuplot: plotB.png
	@gnuplot plotB.gp

plotC.png: funcC.dat plotC.gp
	# Gnuplot: plotC.png
	@gnuplot plotC.gp

plotD.png: funcD.dat plotD.gp
	# Gnuplot: plotD.png
	@gnuplot plotD.gp

funcA.dat: $(BIN_A)
	@./$(BIN_A)
	
funcB.dat: $(BIN_B)
	@./$(BIN_B)

funcC.dat: $(BIN_C)
	@./$(BIN_C)
	
funcD.dat: $(BIN_D)
	@./$(BIN_D)
	
$(BIN_A): $(OBJ_A) $(HEAD_A)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ_A) -o $@ $(LDLIBS)
	
$(BIN_B): $(OBJ_B) $(HEAD_B)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ_B) -o $@ $(LDLIBS)

$(BIN_C): $(OBJ_C) $(HEAD_C)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ_C) -o $@ $(LDLIBS)

$(BIN_D): $(OBJ_D) $(HEAD_D)
	@# Link object files together
	$(LD) $(LDFLAGS) $(OBJ_D) -o $@ $(LDLIBS)

clean:	cleanA cleanB cleanC cleanD

cleanA: 
	@# Remove object files
	rm -f $(OBJ_A) 
	@# Remove binaries
	rm -f $(BIN_A)
	@# Remove datafiles and plot
	rm -f funcA.dat plotA.png

cleanB: 
	@# Remove object files
	rm -f $(OBJ_B) 
	@# Remove binaries
	rm -f $(BIN_B)
	@# Remove datafiles and plot
	rm -f funcB.dat plotB.png

cleanC: 
	@# Remove object files
	rm -f $(OBJ_C) 
	@# Remove binaries
	rm -f $(BIN_C)
	@# Remove datafiles and plot
	rm -f funcC.dat plotC.png

cleanD: 
	@# Remove object files
	rm -f $(OBJ_D) 
	@# Remove binaries
	rm -f $(BIN_D)
	# Removing datafile and plot
	@rm -f funcD.dat plotD.png

htmlfiles: html/mainA.cpp.html html/mainB.cpp.html html/mainC.cpp.html html/mainD.cpp.html html/ode.cpp.html html/check.cpp.html html/check.h.html html/functions.h.html html/ode.h.html html/typedefs.h.html html/vector_arithmetic.h.html html/plotA.gp.html html/plotB.gp.html html/plotC.gp.html html/plotD.gp.html html/Makefile.html
	# Generating HTML files
	rst2html2 README.rst > html/README.html

html/%.html: %
	vim $< +TOhtml +"w $@" +"qall!"


edit:
	@$(EDITOR) Makefile README.rst *.cpp *.h *.gp

