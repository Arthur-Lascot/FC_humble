#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../Image_processing/base_function_on_pict.h"

int init_numbers(SDL_Surface* grid)
{
    display_image(grid);
    wait_for_keypressed();
    
    SDL_Surface* result;
    SDL_Surface* one_B = load_image("../../Ressources/result/1_black.png");
    SDL_Surface* two_B = load_image("../../Ressources/result/2_black.png");
    SDL_Surface* three_B = load_image("../../Ressources/result/3_black.png");
    SDL_Surface* four_B = load_image("../../Ressources/result/4_black.png");
    SDL_Surface* five_B = load_image("../../Ressources/result/5_black.png");
    SDL_Surface* six_B = load_image("../../Ressources/result/6_black.png");
    SDL_Surface* seven_B = load_image("../../Ressources/result/7_black.png");
    SDL_Surface* eight_B = load_image("../../Ressources/result/8_black.png");
    SDL_Surface* nine_B = load_image("../../Ressources/result/9_black.png");

    int h_number = one_B->h;
    int h_square = grid->h/9;
    double coeff = (double)h_square/(double)h_number -2;
    result  = zoomSurface(grid,coeff,coeff,0);

    display_image(result);
    wait_for_keypressed();

    SDL_FreeSurface(one_B);
    SDL_FreeSurface(two_B);
    SDL_FreeSurface(three_B);
    SDL_FreeSurface(four_B);
    SDL_FreeSurface(five_B);
    SDL_FreeSurface(six_B);
    SDL_FreeSurface(seven_B);
    SDL_FreeSurface(eight_B);
    SDL_FreeSurface(nine_B);
    SDL_FreeSurface(grid);
    SDL_FreeSurface(result);
    return 0;
}

int main()
{
    SDL_Surface* grid = load_image("../../Ressources/result/empty_grid.jpg");
    return init_numbers(grid);
}
