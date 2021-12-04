#include <stdlib.h>
#include <SDL.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Image_processing/base_function_on_pict.h"
#include <assert.h>



SDL_Surface* grayscale(char* path)
{
 
    SDL_Surface* image_surface;

    init_sdl();

    image_surface = load_image(path);

    
   
    for ( int i = 0 ; i < image_surface->w ; i++) 
    { 
        for (int j = 0 ; j < image_surface->h ; j++) 
        { 
            Uint32 pixelt = get_pixel(image_surface , i , j); 
            Uint8 r, g, b; 
            SDL_GetRGB(pixelt, image_surface->format, &r, &g, &b); 
            Uint8 col = (r + g +b )/3;
            Uint32 npixel = SDL_MapRGB(image_surface->format,col ,col ,col); 
            put_pixel(image_surface, i, j, npixel); 
        } 
    }
    return image_surface; 
}

/*
int main()
{
    SDL_Surface* image_surface;
	char* path = 	("../../Ressources/image_01.jpeg");
	init_sdl();
	image_surface = grayscale(path);
    image_surface = display_image(image_surface); 
	//SDL_FreeSurface(image_surface); 

	//SDL_FreeSurface(screen_surface);
        
}*/





