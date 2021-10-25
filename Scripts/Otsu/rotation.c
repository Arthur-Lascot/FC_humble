#include <stdlib.h>                                                             
#include <SDL.h>                                                                
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <err.h>                                                                
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"                                              
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




int main(int argc , char** argv)
{
    
    
    if (argc != 2)
        errx(1,"Usage : integers");
    
    
    char* degC = (char*)malloc(sizeof(argv[1]));
    degC = argv[1];
    
    int deg = convert(degC);

    printf("Rotation = %i°\n",deg);
    
    SDL_Surface* image_surface;                                                 

    SDL_Surface* screen;
    SDL_Surface* rotation;

    init_sdl();                                                                 
    char* path= "../../Ressources/image_05.jpeg";                 
    image_surface = load_image(path);
    screen = display_image(image_surface);

    wait_for_keypressed();

    rotation = rotozoomSurface(image_surface, deg, 1.0, 1); 

    screen = display_image(rotation);

    wait_for_keypressed();

    //free(degC);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(rotation);
    SDL_FreeSurface(image_surface);

}

