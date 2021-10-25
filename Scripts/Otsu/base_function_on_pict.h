#ifndef BASE_FUNCTION_ON_PICT_H_
#define BASE_FUNCTION_ON_PICT_H_
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface * rotozoomSurface (SDL_Surface *src, double angle, double zoom, int smooth);
void wait_for_keypressed();
void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void SDL_FreeSurface(SDL_Surface *surface);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen, SDL_Surface* image);


#endif

