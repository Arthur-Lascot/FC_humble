# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS = `pkg-config --libs sdl SDL_image` -lm -lSDL_gfx

OBJ = solver.o
DEP = ${OBJ:.o=.d}

all: solver grid_construct

solver: ${OBJ}

grid_construct: grid_construct.o ../Image_processing/base_function_on_pict.o

grid_construct.o: ../Image_processing/base_function_on_pict.h

base_function_pict.o: ../Image_processing/base_function_on_pict.h


clean:
	${RM} ${OBJ} ${DEP} solver grid_construct

-include ${DEP}

# END

