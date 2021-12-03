#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>
#include <math.h>
#include "base_function_on_pict.h"

void applicate_filter(SDL_Surface* image_surface, double M[], int KS,int weight)
{
    int width = image_surface->w;
    int height = image_surface->h;
    SDL_Surface* work_surface=SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    double S[KS*KS];
    double res = 0;
    for(int m = 0; m<KS*KS;m++)
    {
        S[m]=M[m];
    }
    SDL_BlitSurface(image_surface,NULL,work_surface,NULL);
    Uint32 pixel;
    Uint8 r,g,b;
    int nbvalue = 0;
    for(int i = 0;i<width;i++)
    {
        for(int j = 0; j<height;j++)
        {
            for(int k = -KS/2;k<=KS/2;k++)
            {
                if(i+k>=0 && i+k<width)
                {
                    for(int l = -KS/2;l<=KS/2;l++)
                    {
                        if(j+l>=0 && j+l<height)
                        {
                            pixel = get_pixel(image_surface,i+k,j+l);
                            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                            res += M[nbvalue] * r;
                            nbvalue ++;
                        }
                    }
                }
            }
            res /= weight;
            pixel = 
                SDL_MapRGB(work_surface->format,round(res),round(res),round(res));
            put_pixel(work_surface,i,j,pixel);
            res = 0;
            nbvalue = 0;
        }
    }
    SDL_BlitSurface(work_surface,NULL,image_surface,NULL);
    SDL_FreeSurface(work_surface);
}
