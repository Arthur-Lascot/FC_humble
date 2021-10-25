# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g -fsanitize=address
LDFLAGS= -fsanitize=address
LDLIBS= `pkg-config --libs sdl SDL_image` -lm

all: display cannybis

display: display.o
cannybis: pixel_operations_bis.o cannybis.o

cannybis.o: pixel_operations_bis.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} cannybis

# END
