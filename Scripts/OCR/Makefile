# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g -lm
LDFLAGS =
LDLIBS = -lm

OBJ = forward.o backprop.o network_tools.o reader.o xor.o main.o
DEP = ${OBJ:.o=.d}

all: xor

xor: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} xor

-include ${DEP}

# END

