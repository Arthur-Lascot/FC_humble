#ifndef FILTERING_H
#define FILTERING_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void applicate_filter(SDL_Surface* image_surface,double M[],int KS,int weight);

#endif
