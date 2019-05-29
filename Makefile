# Makefile to compile the solutions for each Daily Coding Problem
GCC = g++
ifdef DEBUG
	CFLAGS = -Wall -g
else
	CFLAGS = -Wall
endif
PROG = a.out
OUTFLAG = -o
EXT = .cc
SRC_DIR = src/
SOURCE = $(SRC_DIR)problem$(MAKECMDGOALS)$(EXT)

help :
	@echo "======================"
	@echo "    Makefile Usage:"
	@echo "======================"
	@echo "   To compile a specific problem type make followed by the problem number."
	@echo "   For example: \n\t make 89\n   will compile problem 89's solution"

$(MAKECMDGOALS) : $(SOURCE)
	$(GCC) $(CFLAGS) $(SOURCE) $(OUTFLAG) $(PROG)

clean:
	rm -f *.o *.out 