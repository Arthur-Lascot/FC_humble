#include <stdlib.h>                                                             
#include <SDL.h>                                                                
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <err.h>                                                                
#include "SDL/SDL_image.h"
#include "../Image_processing/base_function_on_pict.h"                                              
#include <assert.h>


int convert(char arg[])
{
    int res = 0;
    size_t i = 0;
    while (arg[i] != 0)
    {
        if (arg[i] < '0' || arg[i] > '9')
            errx(1,"Error : Parameters Rotation : int");

        int add = arg[i] - '0';
        res = res * 10 + add;
        i++;
    }
    return res;
}




SDL_Surface *rotate(SDL_Surface* image_surface,int deg)
{
    //printf("Rotation = %i°\n",deg);
    
    //SDL_Surface* image_surface;                                                 

    //SDL_Surface* screen;
    SDL_Surface* rotation;

    //init_sdl();                                                                 
    //char* path= "../../Ressources/image_05.jpeg";                 
    //image_surface = load_image(path);
    //screen = display_image(image_surface);

    //wait_for_keypressed();

    rotation = rotozoomSurface(image_surface, deg, 1.0, 1); 

    //SDL_SaveBMP(rotation,"../../Temp/rotationM.bmp");

    //screen = display_image(rotation);

    //wait_for_keypressed();

    //free(degC);
    //SDL_FreeSurface(screen);
    //SDL_FreeSurface(rotation);
    SDL_FreeSurface(image_surface);
    return rotation;
}

