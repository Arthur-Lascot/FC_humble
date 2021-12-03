# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -lSDL_gfx -g -fsanitize=address
LDFLAGS= -lSDL_gfx -fsanitize=address
LDLIBS= `pkg-config --libs sdl SDL_image` -lSDL_gfx

all: base_function_on_pict grayscale rotation


flougaussien.o: base_function_on_pict.h flougaussien.h 

grayscale: base_function_on_pict.h grayscale.h

otsu_function : flougaussien.o base_function_on_pict.o grayscale.o otsu_function.o

rotation: base_function_on_pict.h rotation.h

binarisation.o : base_function_on_pict.h grayscale.h

rotation.o : base_function_on_pict.h 

grayscale.o: base_function_on_pict.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} otsu_function
	${RM} grayscale ${RM} rotation ${RM} flougaussien
# END
