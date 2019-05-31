# Makefile to compile the solutions for each Daily Coding Problem
GCC = g++
ifdef DEBUG
	CFLAGS = -Wall -g -std=c++1z
else
	CFLAGS = -Wall -std=c++1z
endif
PROG = a.out
OUTFLAG = -o
EXT = .cc
SRC_DIR = src/
SOURCE = $(SRC_DIR)problem$(MAKECMDGOALS)$(EXT)
ifeq ($(MAKECMDGOALS),clean)
	GOAL=$(MAKECMDGOALS)_A
else
	GOAL=$(PROG)
endif


help_A:
	@echo "======================"
	@echo "    Makefile Usage:"
	@echo "======================"
	@echo "   To compile a specific problem type make followed by the problem number."
	@echo "   For example: \n\t make 89\n   will compile problem 89's solution"

$(MAKECMDGOALS) : $(GOAL)

.PHONY : $(PROG)
$(PROG) : $(SOURCE)
	$(GCC) $(CFLAGS) $(SOURCE) $(OUTFLAG) $(PROG)

clean_A:
	rm -f *.o *.out 