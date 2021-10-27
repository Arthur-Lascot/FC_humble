#include <stdlib.h>                                                             
#include <SDL.h>                                                                
#include <err.h>                                                                
#include "SDL/SDL.h"                                                            
#include "SDL/SDL_image.h"                                                      
#include "base_function_on_pict.h"                                              
#include "grayscale.h"
#include <assert.h>




int* histo_def ( SDL_Surface* image )   /*define the grayscale's histo */            
{                                                                               
    int* histo = calloc (256 , (sizeof(int)));                  
    for (int i = 0 ; i <= 255 ; i++)                                            
    {                                                                           
        histo[i] = 0; /*initialize the histo at 0 for each color*/               
    }                                                                           
    for ( int i = 0 ; i < image->w ; i++)                                       
    {                                                                           
        for (int j = 0 ; j < image->h ; j++)                                
        {                                                                   
            Uint32 pixelt = get_pixel(image , i , j);                   
            Uint8 r, g, b;                                              
            SDL_GetRGB(pixelt, image->format, &r, &g, &b);              
            histo[(Uint8)r] +=1;                                               
        }                                                                   
    }
    return histo ;                                                              
}                                                                               

int weigth_tot_def(int* histo) /*poids total*/                                  
{                                                                               
    int sum = 0 ;                                                               
    for (int i = 0 ; i<256 ; i++)                                               
    {                                                                           
        sum += i * histo[i];                                                    
    }                                                                           
    return sum;                                                                 
}                                                                               

int find_treshold (int* histo ,int nb_pixel, int weigth_tot)                    
{                                                                               
    int q1 = 0 ;                                                                
    int q2 = 0 ;                                                                
    int sumb = 0;                                                               
    int mu1;                                                                    
    int mu2;                                                                    
    unsigned long int var_between;                                                            
    int seuil = 0;                                                              
    unsigned long int var_max = 0;                                                            
    for (int i = 0 ; i < 256 ; i++)                                             
    {                                               
        q1+= histo[i];
        sumb+=i*histo[i];
        if ( q1!=0 && q1!=nb_pixel )                                            
        {                                                                       
            q2 = nb_pixel - q1 ;                                                 
          //  sumb+=i*histo[i];                                               

            mu1 = sumb/q1;                 

            mu2 = (weigth_tot - sumb) /q2;                                      
            unsigned long int temp = ((mu1-mu2)*(mu1-mu2))/1000;
            unsigned long int tempb = q1/1000*(q2/10000);
            var_between = tempb*temp;                          
            if (var_between >= var_max)                                         
            {                                                                   
                var_max = var_between;                                          
                seuil= i;                                                       
                //printf("%i \n",seuil);
            }                                                                   
        }                                                                       
    }
    return seuil;                                                               
}                                                                               



SDL_Surface* binarisation (char* path)                                          
{   
    /*int* histo[256];                  
    for (int i = 0 ; i <= 255 ; i++)                                            
    {                                                                           
        histo[i] = 0; //initialize the histo at  for each color               
    }                                                                           
    for ( int i = 0 ; i < gray_pict->w ; i++)                                       
    {                                                                           
        for (int j = 0 ; j < gray_pict->h ; j++)                                
        {                                                                   
            Uint32 pixelt = get_pixel(image , i , j);                   
            Uint8 r, g, b;                                              
            SDL_GetRGB(pixelt, image->format, &r, &g, &b);              
            histo[(Uint)r] +=1;                                               
        }                                                                   
    }                                                                           
    return histo ;                                                              
}    */
    SDL_Surface* gray_pict = grayscale (path);
    int nbpixel = gray_pict->w *gray_pict->h;
    int* histo = histo_def(gray_pict);
 
    int weigthtot = weigth_tot_def(histo);
    
   
    int seuil = find_treshold(histo,nbpixel,weigthtot);
    for ( int i = 0 ; i < gray_pict->w ; i++)                                   
    {                                                                           
        for (int j = 0 ; j < gray_pict->h ; j++)                            
        {                                                                   
            Uint32 pixelt = get_pixel(gray_pict, i , j);                    
            Uint8 r, g, b;                                                  
            Uint8 color;                                                    
            SDL_GetRGB(pixelt, gray_pict -> format, &r, &g, &b);            
            if (b>seuil)                                                    
            {                                                               
                color = 255;                                                
            }                                                               
            else                                                            
            {                                                               
                color = 0 ;                                                 
            }

            Uint32 npixel=SDL_MapRGB(gray_pict->format, color , color , color);
            put_pixel(gray_pict, i, j, npixel);                             
        }
    }
    free(histo);
    return gray_pict;
}

int main()
{
    SDL_Surface* image_surface;


    char* path =    ("../../Ressources/image_03.jpeg");                         
    init_sdl();
    image_surface=load_image(path);
    display_image(image_surface);

    SDL_FreeSurface(image_surface);
    wait_for_keypressed();
    image_surface = binarisation(path);
    display_image(image_surface);
    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
}