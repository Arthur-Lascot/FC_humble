#include <stdio.h>
#include "Hough.h"
#include "grayscale.h"
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "base_function_on_pict.h"
#include "canny.h"
#include "square.h"
#include "tools.h"
#include "mean_filter.h"
#include "filtering.h"
#include "../Solver/solver.h"
#include "../Solver/grid_construct.h"

char sudoku[81];

double Mean[25]={
    1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,
    1.0,1.0,1.0,
    1.0,1.0,1.0,1.0,1.0,
    1.0,1.0,1.0,
    1.0,1.0,1.0
};
double gauss3[9]={
    1,2,1,
    2,4,2,
    1,2,1
};

int gauss3W = 16;

double gauss5[25]={
1,4,7,4,1,
4,16,26,16,4,
7,26,41,26,7,
4,16,26,16,4,
1,4,7,4,1
};

int gauss5W = 273;

double gauss7[49]={
0,0,1,2,1,0,0,
0,3,13,22,13,3,0,
1,13,59,97,59,13,1,
2,22,97,159,97,22,2,
1,13,59,97,59,13,1,
0,3,13,22,13,3,0,
0,0,1,2,1,0,0
};

int gauss7W=1003;

char sudokuSolved[81];
char *entrySudo = "entrySudo";
int main()
{
    SDL_Surface* grid = load_image("../../Ressources/result/empty_grid.jpg");
    //char* sudoku = malloc(81*sizeof(char));
    SDL_Surface* image_surface1;
    init_sdl();
    image_surface1 = load_image("../../Ressources/image_01.jpeg");
    SDL_Surface* image_surface = rotozoomSurface(image_surface1,22,1,0);
    SDL_FreeSurface(image_surface1);
    display_image(image_surface);
    wait_for_keypressed();
    image_surface = grayscalebis(image_surface);
    display_image(image_surface);
    wait_for_keypressed();
    for (int i = 0;i<0;i++)
    {
        applicate_filter(image_surface,gauss7,7,gauss7W); 
    }
    for(int i = 0;i<0;i++)
    {
        mean_filter(image_surface);
    }
    display_image(image_surface);
    wait_for_keypressed();
    //SDL_FreeSurface(image_surface);
    //image_surface = canny("../../Ressources/image_09.jpeg");
    printf("Key pressed\n");
    image_surface = hough_line(hough_first(image_surface),image_surface,1);
    int height = image_surface->h;
    int width = image_surface->w;
    double coeff = 1;
    SDL_Surface* init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
    /*
       if(height>width)
       {
       if(height>800)
       {
       coeff = 800/(double)height;
       init_surface = zoomSurface(init_surface,coeff,coeff,0);
       }
       }
       else
       {
       if (width>800)
       {
       coeff = 800/(double)height;
       init_surface = zoomSurface(init_surface,coeff,coeff,0);

       }
       }
     */
    display_image(init_surface);
    wait_for_keypressed();
    free(init_surface);
    printf("Square column called\n");
    List* column = square_column(image_surface);
    printf("Square line called\n");
    List* line = square_line(image_surface);
    printf("DrawSquare called\n");
    DrawSquare(image_surface,column,line);
    printf("End of drawing\n");
    init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(image_surface,NULL,init_surface,NULL);

    if(height>width)
    {
        if(height>800)
        {
            coeff = 800/(double)height;
            init_surface = zoomSurface(init_surface,coeff,coeff,0);
        }
    }
    else
    {
        if (width>800)
        {
            coeff = 800/(double)height;
            init_surface = zoomSurface(init_surface,coeff,coeff,0);

        }
    }

    display_image(init_surface);
    wait_for_keypressed();
    free(init_surface);

    //display_image(image_surface);
    //wait_for_keypressed()i;
    FILE *entry_sudoku = fopen(entrySudo,"w");
    WriteFile(entry_sudoku,sudoku);
    solveMain("entrySudo");
    entry_sudoku = fopen("entrySudo.result","r");
    readFile(entry_sudoku,sudokuSolved);
    init_numbers(grid,sudoku);
    fill_numbers(grid,sudokuSolved,sudoku);
    //printf("Key pressed\n");
    SDL_FreeSurface(image_surface);
    /* image_surface = load_image("../../Ressources/image_03.jpeg");
       display_image(image_surface);
       wait_for_keypressed();
       SDL_FreeSurface(image_surface);
       image_surface = canny("../../Ressources/image_03.jpeg");
       printf("Key pressed\n");
       image_surface = hough_line(hough(image_surface),image_surface);
       display_image(image_surface);
       wait_for_keypressed();
       printf("Square column called\n");
       column = square_column(image_surface);
       printf("Square line called\n");
       line = square_line(image_surface);
       printf("DrawSquare called\n");
       image_surface = DrawSquare(image_surface,column,line);
       printf("End of drawing\n");
       display_image(image_surface);
       wait_for_keypressed();
    //printf("Key pressed\n");
    SDL_FreeSurface(image_surface);
    image_surface = load_image("../../Ressources/image_08.jpg");
    display_image(image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    image_surface = canny("../../Ressources/image_08.jpg");
    printf("Key pressed\n");
    image_surface = hough_line(hough(image_surface),image_surface);
    display_image(image_surface);
    wait_for_keypressed();
    printf("Square column called\n");
    column = square_column(image_surface);
    printf("Square line called\n");
    line = square_line(image_surface);
    printf("DrawSquare called\n");
    image_surface = DrawSquare(image_surface,column,line);
    printf("End of drawing\n");
    display_image(image_surface);
    wait_for_keypressed();
    //printf("Key pressed\n");
    SDL_FreeSurface(image_surface);
    printf("Done\n");*/
    return 0;
}
