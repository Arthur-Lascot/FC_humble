#ifndef HOUGH_H_
#define HOUGH_H_
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
unsigned int* hough_first(SDL_Surface* image_surface);
SDL_Surface* hough_line(unsigned int* hough,SDL_Surface* image_surface,
int to_rotate,int click);
#endif
