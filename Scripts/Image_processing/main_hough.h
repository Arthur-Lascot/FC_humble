#ifndef _MAIN_HOUGH_H_

#define _MAIN_HOUGH_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int degrot;

char nameGrid[128];

int thresh_otsu;

void resize(SDL_Surface* image_surface, char* to_display,int touse);

int mainHough(int click,char *pathImg);


#endif
