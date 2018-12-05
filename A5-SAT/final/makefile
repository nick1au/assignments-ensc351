## This is a simple Makefile with lots of comments
## Check Unix Programming Tools handout for more info.

# Define what compiler to use and the flags.
CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Werror -fopenmp

all: sat

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.c
	$(CC) -c $(CCFLAGS) $<

sat: stack.o sat.o
	$(CC) -o sat stack.o sat.o $(CCFLAGS)

clean:
	rm -f core *.o sat

