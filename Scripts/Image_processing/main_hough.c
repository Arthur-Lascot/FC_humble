#include <stdio.h>
#include "Hough.h"
//#include "grayscale.h"
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "base_function_on_pict.h"
#include "canny.h"
#include "square.h"
#include "tools.h"
#include "../Solver/solver.h"
#include "../Solver/grid_construct.h"


char sudoku[81];
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
    //SDL_FreeSurface(image_surface);
    //image_surface = canny("../../Ressources/image_09.jpeg");
    printf("Key pressed\n");
    image_surface = hough_line(hough_first(image_surface),image_surface,1);
    display_image(image_surface);
    wait_for_keypressed();
    printf("Square column called\n");
    List* column = square_column(image_surface);
    printf("Square line called\n");
    List* line = square_line(image_surface);
    printf("DrawSquare called\n");
    DrawSquare(image_surface,column,line);
    printf("End of drawing\n");
    display_image(image_surface);
    wait_for_keypressed();
    FILE *entry_sudoku = fopen(entrySudo,"w");
    WriteFile(entry_sudoku,sudoku);
    solveMain("entrySudo");
    entry_sudoku = fopen("entrySudo.result","r");
    readFile(entry_sudoku);
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
