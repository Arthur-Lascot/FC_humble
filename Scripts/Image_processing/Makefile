# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3 -g -fsanitize=address 
LDFLAGS= -fsanitize=address
LDLIBS= `pkg-config --libs sdl SDL_image` -lm -lSDL_gfx

all: main_hough display base_function_on_pict grayscale rotation

display: display.o

main_hough: main_hough.o base_function_on_pict.o Hough.o tools.o canny.o square.o ../Solver/solver.o ../Solver/grid_construct.o mean_filter.o filtering.o  ../OCR/xor.o ../OCR/forward.o ../OCR/backprop.o ../OCR/network_tools.o ../OCR/reader.o ../Otsu/otsu_function.o
    
main_hough.o: Hough.h base_function_on_pict.h tools.h canny.h square.h mean_filter.h filtering.h ../Solver/solver.h ../Solver/grid_construct.h ../Otsu/otsu_function.h

Hough.o: tools.h base_function_on_pict.h

square.o:base_function_on_pict.h tools.h square.h ../OCR/xor.h ../OCR/forward.h ../OCR/backprop.h ../OCR/network_tools.h ../OCR/reader.h

base_function_on_pict.o: base_function_on_pict.h

canny.o: base_function_on_pict.h

mean_filter.o: mean_filter.h

filtering.o: filtering.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} *.BMP
	${RM} display ${RM} main_hough

# END
