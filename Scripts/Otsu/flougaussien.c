#include <stdlib.h>
#include <SDL.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Image_processing/base_function_on_pict.h"
#include <assert.h>

/*int matgaus[25] = {2 , 4 , 5 , 4 , 2 ,
                    4 , 9 , 12 , 9 , 4 ,
                    5 , 12 , 15 , 12 , 5 ,
                    4 , 9 , 12 , 9 , 4 ,
                    2 , 4 , 5 , 4 , 1 };
*/

double matgaus[25] = {0.0030 , 0.0133 , 0.0219 , 0.0133 , 0.0030,
                   0.0133 , 0.0596 , 0.0983 , 0.0596 , 0.0133,
                   0.0219 , 0.0983 , 0.1621 , 0.0983 , 0.0219,
                   0.0133 , 0.0596 , 0.0983 , 0.0596 , 0.0133,
                   0.0030 , 0.0133 , 0.0219 , 0.0133 , 0.0030};

SDL_Surface* flougaussien(SDL_Surface* image )
{
    for(int i = 3 ; i < (image -> h)-3; i++)
    {
        for (int j = 3 ; j < (image -> w)-3 ; j++)
        {
            double sumpixtemp = 0 ;
            for (int k = 0 ; k < 5 ; k++)
            {
                for (int l = 0 ; l < 5 ; l++)
                {
                    Uint32 pixcoltemp = get_pixel(image ,j+l-2 , i+ k - 2 );
                    Uint8 r, g, b; 
                    SDL_GetRGB(pixcoltemp,image->format, &r, &g, &b); 
                    sumpixtemp += r * matgaus[k*5 + l];
                  
                }
            }
            Uint8 colf= sumpixtemp; // 158;
            Uint32 npixel = SDL_MapRGB(image->format,colf,colf,colf);
            put_pixel(image , j , i , npixel);
        }
    }
    return image;
}


