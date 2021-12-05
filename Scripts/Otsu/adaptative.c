#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "../Image_processing/base_function_on_pict.h"
#include <stdio.h>

int Clamp(int a,int low,int high)
{
    if(a<low)
    {
        return low;
    }
    else if(a>high)
    {
        return high;
    }
    else
    {
        return a;
    }
}

int Min(int a, int b)
{
    return a>b?b:a;
}

SDL_Surface* adaptative_threshold(SDL_Surface* image_surface,int t)
{
   
    SDL_Surface* result=
    SDL_CreateRGBSurface(0,image_surface->w,image_surface->h,32,0,0,0,0); 
    long long* Im= calloc(image_surface->w*image_surface->h,sizeof(long long));
    long long sum;
    int x1;
    int x2;
    int y1;
    int y2;
    int s =  (Min(image_surface->w,image_surface->h))/16;
    long long lt = (long long) t;
    int count;
    Uint32 pixel;
    Uint8 r,g,b;
    for(int i = 0;i<image_surface->w;i++)
    {
        sum = 0;
        for(int j = 0;j< image_surface->h;j++)
        {
            pixel = get_pixel(image_surface,i,j);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            sum+=(long long)r;
            if(i == 0){
                Im[j]=sum;
            }
            else
            {
                Im[j*image_surface->w+i]=Im[j*image_surface->w+(i-1)]+sum;

            }
        }
    }
    for(int i = 0;i<image_surface->w;i++)
    {
        for(int j = 0; j< image_surface->h;j++)
        {
            x1=Clamp(i-s,1,image_surface->w-1);
            x2=Clamp(i+s,0,image_surface->w-1);
            y1=Clamp(j-s,1, image_surface->h-1);
            y2=Clamp(j+s,0, image_surface->h-1);
            count=(x2-x1)*(y2-y1);
            sum = Im[y2*image_surface->w+x2]-
            Im[(y1-1)*image_surface->w+x2]-
            Im[y2*image_surface->w+(x1-1)]+
            Im[(y1-1)*image_surface->w+(x1-1)];
            pixel = get_pixel(image_surface,i,j);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            if(r*(long long)count<=(sum*(100-lt)/100)){
                pixel = SDL_MapRGB(image_surface->format,0,0,0);
            }
            else
            {
                 pixel = SDL_MapRGB(image_surface->format,255,255,255);

            }
            put_pixel(result,i,j,pixel);
        }
    }
    SDL_FreeSurface(image_surface);
    free(Im);
    return result;
}
/*
int main()
{
    init_sdl();
    SDL_Surface* test = load_image("../../Ressources/image_06.jpeg");
    display_image(test);
    wait_for_keypressed();
    test = adaptative_threshold(test);
    display_image(test);
    wait_for_keypressed();
    SDL_FreeSurface(test);
    return 0;
}
*/
