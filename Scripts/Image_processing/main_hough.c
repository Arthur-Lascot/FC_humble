#include <stdio.h>
#include "Hough.h"
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
#include "../Otsu/otsu_function.h"
#include "../Otsu/adaptative.h"
#include "../Otsu/rotation.h"
#include "main_hough.h"

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

void resize(SDL_Surface* image_surface,char* to_display,int touse)
{
    double coeff;
    int height = image_surface->h;
    int width = image_surface->w;
    SDL_Surface* init_surface;
    if(height>width)
    {
        if(height>800)
        {
            coeff = 800/(double)height;
            init_surface = zoomSurface(image_surface,coeff,coeff,0);
        }
        else
        {
            init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
            SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
        }
    }
    else
    {
        if (width>800)
        {
            coeff = 800/(double)height;
            init_surface = zoomSurface(image_surface,coeff,coeff,0);
        }   
        else
        {
            init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
            SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
        }
    }
    SDL_SaveBMP(init_surface,to_display);

    if (touse)
        SDL_SaveBMP(image_surface,"./Temp/use.bmp");

    SDL_FreeSurface(init_surface);
    SDL_FreeSurface(image_surface);
}

char sudokuSolved[81];
char *entrySudo = "entrySudo";
int mainHough(int click,char *pathImg)
{
    SDL_Surface* grid = load_image("./Ressources/result/empty_grid.jpg");
    //char* sudoku = malloc(81*sizeof(char));
    SDL_Surface* image_surface;
    init_sdl();
    if(click != 0)
    {
        image_surface = load_image(pathImg);
        //SDL_Surface* image_surface = rotozoomSurface(image_surface1,22,1,0);
        //SDL_FreeSurface(image_surface1);
        //display_image(image_surface);
        //wait_for_keypressed();
        if(click==-2){
            resize(image_surface,"./Temp/image.bmp",1);
            return 0;}
        if(click==-1) //Rotate Manual Right
        {
            image_surface = rotate(image_surface,degrot);
            resize(image_surface,"./Temp/imagerot.bmp",0);
            return 0;
        }
        image_surface = grayscalebis(image_surface);
        //display_image(image_surface);
        //wait_for_keypressed();
        if(click==1){
            resize(image_surface,"./Temp/grayscale.bmp",0);
            return 0;}
        if(click==2){
            applicate_filter(image_surface,gauss3,3,gauss3W);
            resize(image_surface,"./Temp/gauss3.bmp",1);
            return 0;
        }
        if(click==3)
        {
            applicate_filter(image_surface,gauss5,5,gauss5W); 
            resize(image_surface,"./Temp/gauss5.bmp",1);
            return 0;
        }
        if (click == 4)
        {
            applicate_filter(image_surface,gauss7,7,gauss7W); 
            resize(image_surface,"./Temp/gauss7.bmp",1);
            return 0;
        }
        if(click==5)
        {
            mean_filter(image_surface);
            resize(image_surface,"./Temp/median.bmp",1);
            return 0;
        }

        //SDL_FreeSurface(image_surface);
        //image_surface = canny("../../Ressources/image_09.jpeg");
        //printf("Key pressed\n");

        image_surface = adaptative_threshold(image_surface,thresh_otsu);

        //display_image(image_surface);
        //wait_for_keypressed();
        if(click==6)
        {
            printf("Threshold : %i",thresh_otsu);
            resize(image_surface,"./Temp/otsu.bmp",0);
            return 0;
        }
        if(click==7)
        {
            image_surface = canny(image_surface);
            resize(image_surface,"./Temp/canny.bmp",0);
            return 0;
        }
        image_surface = hough_line(hough_first(image_surface),image_surface,1,click);
        if(click == 8)
        {
            resize(image_surface,"./Temp/auto_rotate.bmp",0);
            return 0;
        }
        if(click == 9)
        {
            resize(image_surface,"./Temp/hough.bmp",0);
            return 0;
        }
        /*SDL_Surface* init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
          SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
          display_image(init_surface);
          wait_for_keypressed();
          SDL_FreeSurface(init_surface);
         */
        //printf("Square column called\n");
        List* column = square_column(image_surface);
        //printf("Square line called\n");
        List* line = square_line(image_surface);
        if(column == NULL||line==NULL)
        {
            SDL_FreeSurface(image_surface);
            image_surface = load_image("./Ressources/error.png");
            switch(click)
            {
                case 10:
                    resize(image_surface,"./Temp/square.bmp",0);
                    break;
                case 11:
                    resize(image_surface,"./Temp/traitement.bmp",0);
                    break;
                case 0:
                    resize(image_surface,"./Temp/solved.bmp",0);
                    break;
                default:
                    resize(image_surface,"./Temp/default.bmp",0);
                    break;
            }
            return 1;
        }

        printf("DrawSquare called\n");
        DrawSquare(image_surface,column,line);
        if(click == 10)
        {
            resize(image_surface,"./Temp/square.bmp",0);
            return 0;
        }
        printf("End of drawing\n");
        //init_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
        //SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
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
        /*
           display_image(init_surface);
           wait_for_keypressed();
           SDL_FreeSurface(init_surface);
         */
        //display_image(image_surface);
        //wait_for_keypressed()i;
        FILE *entry_sudoku = fopen(nameGrid,"w");
        WriteFile(entry_sudoku,sudoku);
        if(click == 11)
        {
            resize(image_surface,"./Temp/traitement.bmp",0);
            return 0;
        }
    }
    FILE *OldSudo = fopen(nameGrid,"r");
    readFile(OldSudo,sudoku);
    int is_valid = solveMain(nameGrid);
    if(is_valid == 404 && click ==0)
    {
        image_surface = load_image("./Ressources/error404.png");
        resize(image_surface,"./Temp/solved.bmp",0);
        return 1;

    }
    //sprintf(nameGrid,"%s.result",nameGrid);
    char * nameRes = concatF(nameGrid,".result");
    FILE *entry_sudoku = fopen(nameRes,"r");
    readFile(entry_sudoku,sudokuSolved);
    image_surface =fill_numbers(init_numbers(grid,sudoku),sudokuSolved,sudoku);
    if(click == 0)
    {
        resize(image_surface,"./Temp/solved.bmp",0);
        return 0;
    }
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
    return 1;
}
