#include <err.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
#include "canny.h"
#include <math.h>

SDL_Surface* grayscalebis(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;
    Uint32 pixel;
    Uint8 r, g, b;
    int average = 0;
    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<height;j++)
        {
            pixel = get_pixel(image_surface,i,j);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            average = 0.3*r+0.59*g+0.11*b;
            pixel=SDL_MapRGB(image_surface->format, average, average, average);
            put_pixel(image_surface, i, j, pixel);
        }
    }
    return image_surface;
}


SDL_Surface* canny(SDL_Surface* first_surface)
{
    int width = first_surface->w;
    int height = first_surface->h;
    Uint32 pixel1,pixel2,pixel3;
    int one,two,three,threebis,four,five,six,seven,sevenbis,eight,nine,fivebis;
    int sum;
    Uint8 r, g, b;
    int highThreshold;
    int lowThreshold;
    double * directions = (double *) calloc(width*height,sizeof(double));
    SDL_Surface* image_surface=SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_Surface* max_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
SDL_Surface* thresh_surface=SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    
    SDL_BlitSurface(first_surface,NULL,image_surface,NULL);
    SDL_BlitSurface(image_surface,NULL,max_surface,NULL);
    SDL_BlitSurface(max_surface,NULL,thresh_surface,NULL);
    max_surface = grayscalebis(max_surface);
    thresh_surface = grayscalebis(thresh_surface);

    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<height;j++)
        {
            if(i == 0 && j==0)
            {   
                one = 0;
                two = 0;
                three = 0;
                threebis = 0;
                four = 0;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2);
                seven = 0;
                sevenbis = 0;
                pixel1 = get_pixel(image_surface,i,j+i);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                pixel1 = get_pixel(image_surface,i+1,j+i);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                nine = r*(-1);      
            }
            else if(j==0 && i == width-1)
            {
                one = 0;
                two = 0;
                three = 0;
                threebis = 0;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
		six = 0;
                pixel1 = get_pixel(image_surface,i-1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                seven = r;
                sevenbis = r*(-1);
                pixel1 = get_pixel(image_surface,i,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                nine = 0;

            }
            else if(j == 0)
            {
                one = 0;
                two = 0;
                three = 0;
                threebis = 0;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2);
                pixel1 = get_pixel(image_surface,i-1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                seven = r;
                sevenbis = r*(-1);
                pixel1 = get_pixel(image_surface,i,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                pixel1 = get_pixel(image_surface,i+1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                nine = r*(-1);
                                                                           
            }
            else if(i == 0 && j == height-1)
            {
                one = 0;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                pixel1 = get_pixel(image_surface,i+1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                three = r*(-1);
                threebis = r;                
                four = 0;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2); 
                seven = 0;
                sevenbis = 0;
                eight = 0;
                nine = 0;

            }
            else if(i == 0)
            {
                one = 0;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                pixel1 = get_pixel(image_surface,i+1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                three = r*(-1);
                threebis = r;                
                four = 0;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2); 
                seven = 0;
                sevenbis = 0;
                pixel1 = get_pixel(image_surface,i,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                pixel1 = get_pixel(image_surface,i+1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                nine = r*(-1);
            }
            else if(i == width-1 && j == height-1)
            {
                pixel1 = get_pixel(image_surface,i-1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                one = r;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                three = 0;
                threebis = 0;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
                six = 0;
                seven = 0;
                sevenbis = 0;
                eight = 0;
                nine = 0;
            }
            else if(j == height-1)
            {
                pixel1 = get_pixel(image_surface,i-1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                one = r;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                pixel1 = get_pixel(image_surface,i+1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                three = r*(-1);
                threebis = r;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2);
                seven = 0;
                eight = 0;
                nine = 0;
            }
            else if(i == width-1)
            {
                pixel1 = get_pixel(image_surface,i-1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                one = r;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                three = 0;
                threebis = 0;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
                six = 0;
                pixel1 = get_pixel(image_surface,i-1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                seven = r;
                sevenbis = r*(-1);
                pixel1 = get_pixel(image_surface,i,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                nine = 0;
            }
            else
            {
                pixel1 = get_pixel(image_surface,i-1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                one = r;
                pixel1 = get_pixel(image_surface,i,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                two = r*2;
                pixel1 = get_pixel(image_surface,i+1,j-1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                three = r*(-1);
                threebis = r;
                pixel1 = get_pixel(image_surface,i-1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                four = r*2;
                pixel1 = get_pixel(image_surface,i+1,j);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                six = r*(-2);
                pixel1 = get_pixel(image_surface,i-1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                seven = r;
                sevenbis = r*(-1);
                pixel1 = get_pixel(image_surface,i,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                eight = r*(-2);
                pixel1 = get_pixel(image_surface,i+1,j+1);
                SDL_GetRGB(pixel1,image_surface->format,&r,&g,&b);
                nine = r*(-1);
            }
            five = one + two + three + four + six + seven + eight + nine;
            fivebis=one+ two + threebis + four + six + sevenbis + eight + nine;
            directions[j*width+i] = atan2(fivebis,five);
            five = abs(five);
            fivebis = abs(fivebis);
            if(five > 255)
            {
                five = 255;
            }
            if (fivebis > 255)
            {
                fivebis = 255;
            }
            sum = five + fivebis;
            if(sum > 255)
            {
                sum = 255;
            }
            pixel3 = SDL_MapRGB(thresh_surface->format, sum, sum, sum);
            put_pixel(max_surface,i,j,pixel3);
            put_pixel(thresh_surface,i,j,pixel3);
        }
    }


    int q;
    int s;
    double degree;

    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<height;j++)
        {
            degree = 180*directions[j*width+i]/M_PI;
            
            if(degree < 0)
            {
                degree += 180;
            }
            if(degree<22.5 ||degree>=157.5)
            {
                if(i == width-1)
                {
                    q = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i+1,j);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    q = r;
                }
                if(i == 0)
                {
                    s = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i-1,j);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    s = r;
                }
            }
            else if(degree<67.5)
            {
                if(i == 0 ||j == (height-1))
                {
                    q = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i-1,j+1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    q = r;
                }
                if(i == (width - 1)||j == 0)
                {
                    s = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i+1,j-1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    s = r;
                }
            }
            else if(degree<112.5)
            {
                if(j == height-1)
                {
                    q = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i,j+1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    q = r;
                }
                if(j == 0)
                {
                    s = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i,j-1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    s = r;
                }
            }
            else
            {
                if(i == 0 ||j == 0)
                {
                    q = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i-1,j-1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    q = r;
                }
                if(i == width - 1||j == (height-1))
                {
                    s = 0; 
                }
                else
                {
                    pixel1 = get_pixel(max_surface,i+1,j+1);
                    SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    s = r;
                }
            }
            pixel1 = get_pixel(max_surface,i,j);
            SDL_GetRGB(pixel1,max_surface->format,&r,&g,&b);
                    
            if(r<q ||r<s)
            {
                pixel1 = SDL_MapRGB(max_surface->format, 0, 0, 0);
                put_pixel(max_surface,i,j,pixel1);
                put_pixel(thresh_surface,i,j,pixel1);
            }

        }
    }

    free(directions);
    
    

    //Threshold
    highThreshold = 200;
    lowThreshold = 76;
    int check;

    for(int i = 0;i<width;i++)
    {
        for(int j = 0;j<height;j++)
        {
            check = 0;
            pixel1 = get_pixel(thresh_surface,i,j);
            SDL_GetRGB(pixel1,thresh_surface->format,&r,&g,&b);
            if(r>=highThreshold)
            {
                pixel1 = SDL_MapRGB(thresh_surface->format, 255, 255, 255);
                
            }
            else if(r<lowThreshold)
            {
                pixel1 = SDL_MapRGB(thresh_surface->format, 0, 0, 0);
            }
            else
            {
                if(i == 0 && j == 0)
                {
                    for(int k=0; k<2;k++)
                    {
                        for(int l=0;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                 continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }

                }
                else if(i == 0 && j == height-1)
                {
                    for(int k=0; k<2;k++)
                    {
                        for(int l=-1;l<1;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }

                }
                else if(j == 0 && i == width-1)
                {
                    for(int k=-1; k<1;k++)
                    {
                        for(int l=0;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }

                else if(i == 0)
                {
                    for(int k=0; k<2;k++)
                    {
                        for(int l=-1;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }

                }
                else if(j == 0)
                {
                    for(int k=-1; k<2;k++)
                    {
                        for(int l=0;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }
                else if(i == width-1 && j == height -1)
                {
                    for(int k=-1; k<1;k++)
                    {
                        for(int l=-1;l<1;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }
                else if(i == width-1)
                {
                    for(int k=-1; k<1;k++)
                    {
                        for(int l=-1;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }
                else if(j == height-1)
                {
                    for(int k=-1; k<2;k++)
                    {
                        for(int l=-1;l<1;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }
                else
                {
                    for(int k=-1; k<2;k++)
                    {
                        for(int l=-1;l<2;l++)
                        {
                            if(l == 0 && k ==0)
                            {
                                continue;
                            }
                            pixel2 = get_pixel(thresh_surface,i+k,j+l);
                            SDL_GetRGB(pixel2,thresh_surface->format,&r,&g,&b);
                            if(r>=highThreshold)
                            {
                                check = 1;
                            }
                        }
                    }
                }
                if(check == 0)
                {
                    pixel1 = SDL_MapRGB(thresh_surface->format,0,0,0);
                }
                else
                {
                    pixel1 = SDL_MapRGB(thresh_surface->format,255,255,255);
                }
            }
            put_pixel(thresh_surface,i,j,pixel1);
        }
    }
    printf("hey\n");
    //display_image(image_surface);
    //wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(max_surface);
    return thresh_surface;
}
