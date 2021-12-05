#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include "../Image_processing/base_function_on_pict.h"

SDL_Surface* init_numbers(SDL_Surface* grid  ,char sudoku[])
{
    //display_image(grid);
    //wait_for_keypressed();

    SDL_Surface* result;
    SDL_Surface* number = load_image("./Ressources/result/1_black.png");
    int h_number = number->h;
    SDL_FreeSurface(number);
    int h_square = grid->h/9;
    double coeff = -0.2-(double)h_number/(double)h_square;
    result  = zoomSurface(grid,coeff,coeff,0);
    h_square = result->h/9;
    SDL_Rect rect;
    rect.x= 32;
    rect.y= 10;
    rect.w= h_square;
    rect.h= h_square;
    for (int i = 0;i<9;i++)
    {
        for(int j = 0; j<9;j++)
        {
            switch(sudoku[i*9+j])
            {
                case '1':
                    number = load_image("./Ressources/result/1_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;
                case '2':
                    number = load_image("./Ressources/result/2_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '3':
                    number = load_image("./Ressources/result/3_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '4':
                    number = load_image("./Ressources/result/4_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '5':
                    number = load_image("./Ressources/result/5_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '6':
                    number = load_image("./Ressources/result/6_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '7':
                    number = load_image("./Ressources/result/7_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '8':
                    number = load_image("./Ressources/result/8_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                case '9':
                    number = load_image("./Ressources/result/9_black.png");
                    SDL_BlitSurface(number,NULL,result,&rect);
                    SDL_FreeSurface(number);
                    break;

                default:
                    break;
            }
            rect.x += h_square;
        }
        rect.x -= 9*(h_square);
        rect.y += h_square;
    }
    //display_image(result);
    //wait_for_keypressed();

    //SDL_FreeSurface(number);
    SDL_FreeSurface(grid);
    //SDL_FreeSurface(result);
    return result;
}

SDL_Surface* fill_numbers(SDL_Surface* result  ,char sudoku[],char oldsudoku[])
{
    int h_square = result->h/9;
    SDL_Surface *number;
    SDL_Rect rect;
    rect.x= 32;
    rect.y= 10;
    rect.w= h_square;
    rect.h= h_square;
    for (int i = 0;i<9;i++)
    {
        for(int j = 0; j<9;j++)
        {
            if(oldsudoku[i*9+j]=='.')
            {
                switch(sudoku[i*9+j])
                {
                    case '1':
                        number = load_image("./Ressources/result/1_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;
                    case '2':
                        number = load_image("./Ressources/result/2_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '3':
                        number = load_image("./Ressources/result/3_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '4':
                        number = load_image("./Ressources/result/4_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '5':
                        number = load_image("./Ressources/result/5_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '6':
                        number = load_image("./Ressources/result/6_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '7':
                        number = load_image("./Ressources/result/7_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '8':
                        number = load_image("./Ressources/result/8_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    case '9':
                        number = load_image("./Ressources/result/9_red.png");
                        SDL_BlitSurface(number,NULL,result,&rect);
                        SDL_FreeSurface(number);
                        break;

                    default:
                        break;
                }
            }
            rect.x += h_square;
        }
        rect.x -= 9*(h_square);
        rect.y += h_square;
    }
    //display_image(result);
    //wait_for_keypressed();

    //SDL_FreeSurface(number);
    return result;
}

