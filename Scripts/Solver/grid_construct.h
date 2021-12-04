#ifndef GRID_CONSTRUCT_H
#define GRID_CONSTRUCT_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

SDL_Surface* init_numbers(SDL_Surface *grid,char sudoku[]);
int fill_numbers(SDL_Surface *result,char sudoku[],char oldSudoku[]);

#endif
