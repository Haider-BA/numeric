# Define compiler
CC=g++

# Define compiler flags (show all warnings)
CCFLAGS=-Wall

# Define linker
LD=g++

# Define linker flags
LDFLAGS=

# Filenames of source code
ASRC=$(shell ls *.A.cpp)
BSRC=$(shell ls *.B.cpp)

# Filenames of object files
BOBJ=$(BSRC:.cpp=.o)

# Remove file type extension for binary filename
ABIN=$(ASRC:.cpp=)
BBIN=hello_user.B

# The default "all" depends on A and B

all:	A B 

correct: 
	# Cenerating correct answer
	@echo "Hello, $(USER)" > correct.txt

A:
	# Compile source code
	$(CC) $(CCFLAGS) $(ASRC) -o $(ABIN)
	# Execute program and redirect stdout to file
	./$(ABIN) > out.A.txt

B:	$(BOBJ)
	# Link object files together
	$(LD) $(LDFLAGS) $(BOBJ) -o $(BBIN)
	# Execute program and redirect stdout to file
	./$(BBIN) > out.B.txt
	
# Object files for B require B source code files
.B.o:	$(BSRC)
	$(CC) $(CCFLAGS) -c $< -o $@

clean-A:
	# Remove binary
	rm -f $(ABIN)

clean-B: 
	# Remove object files
	rm -f $(BOBJ)
	# Remove binary
	rm -f $(BBIN)

clean:	clean-A clean-B
	rm -f correct.txt

test-A:	correct A
	@echo "Checking A... "
	@diff --brief correct.txt out.A.txt
	@echo "done"

test-B:	correct B
	@echo "Checking B... "
	@diff --brief correct.txt out.B.txt
	@echo "done"

test:	test-A test-B
