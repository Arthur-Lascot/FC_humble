#ifndef ADAPTATIVE_H
#define ADAPTATIVE_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int Clamp(int a, int low, int high);
int Min(int a, int b);
SDL_Surface* adaptative_threshold(SDL_Surface* image_surface, int t);

#endif
