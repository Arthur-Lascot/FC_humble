#ifndef OTSU_FUNCTION_H
#define OTSU_FUNCTION_H
#include <stdlib.h>
#include <SDL.h>

SDL_Surface* otsuadapt (SDL_Surface* image,int t);
SDL_Surface* filtre(SDL_Surface* image_surface,int t); 

#endif

