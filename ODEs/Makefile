#!/bin/env make

SHELL = /bin/sh
CC = g++
CFLAGS = -Wall -O3
OBJ = rkdriver.o rkstep.o
BIN = ode

all: $(BIN) ODE.output ode.png

ODE.output: $(BIN)
	./$(BIN) > ODE.output

$(BIN): main.o rkdriver.o rkstep.o
	$(CC) $(CFLAGS) -o $(BIN) main.o $(OBJ)

clean:
	rm -f $(BIN) *.txt *~ *.output *.png *.o

%.png: plot.gp
	gnuplot < $<

edit:
	vim -p Makefile *.cpp *.gp
