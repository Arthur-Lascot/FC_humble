# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS = -lm

OBJ = solver.o
DEP = ${OBJ:.o=.d}

all: solver

solver: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} solver

-include ${DEP}

# END

