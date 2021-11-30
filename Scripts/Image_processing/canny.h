#ifndef CANNY_H
#define CANNY_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

SDL_Surface* grayscalebis(SDL_Surface* image_surface);
SDL_Surface* canny(SDL_Surface* image_surface);

#endif
