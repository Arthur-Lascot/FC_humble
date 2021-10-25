#include <stdlib.h>
#include <SDL.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
#include <assert.h>


SDL_Surface* grayscale(char* path)
{
 
    SDL_Surface* image_surface;

    init_sdl();

    image_surface = load_image(path);

    
   
    for ( int i = 0 ; i < image_surface->w ; i++) 
    { 
        for (int j = 0 ; j < image_surface->h ; j++) 
        { 
            Uint32 pixelt = get_pixel(image_surface , i , j); 
            Uint8 r, g, b; 
            SDL_GetRGB(pixelt, image_surface->format, &r, &g, &b);
            Uint32 npixel = 
            SDL_MapRGB(image_surface->format,(r + g+ b)/3,
            (r + g +b)/3,(r +g + b)/3); 
            put_pixel(image_surface, i, j, npixel); 
        } 
    } 
    return image_surface; 
}

float* histo_average_def ( SDL_Surface* image )
{
	int histo[256];
	int nbpixel = image->h * image->w ;
	for (int i = 0 ; i <= 255 ; i++)
	{
		histo[i] = 0;
	}
	for ( int i = 0 ; i < image->w ; i++)
	{
       		for (int j = 0 ; j < image->h ; j++)
        	{
            		Uint32 pixelt = get_pixel(image , i , j);
            		Uint8 r, g, b;
            		SDL_GetRGB(pixelt, image->format, &r, &g, &b);
            		histo[r] +=1;
			
		}
    	}
	float* histo_proba= malloc (256 * (sizeof(float)));
	for (int i = 0 ; i <= 255 ; i++)
	{
		histo_proba[i] = 0;
	}

	for (int i= 0; i <256 ; i++)
	{
		histo_proba[i]=(float)histo[i]/(float)nbpixel;
	}
	
	return histo_proba ;
}


float average1(float* histo,float t)
{
	float average= 0;
	for (int i = 0 ; i < t; i++)
	{
		average +=histo[i] * i; 
	}
	return average;
}

float average2(float* histo,float t)
{
	float average= 0;
	for (int i = t ; i < 256; i++)
	{
		average +=histo[i] * i; 
	}
	return average;
}

float average_variance_1_and_2(float*histo,int t,float average1,float average2)
{
	float v1 = 0;
	for (int i = 0 ; i <= t ; i++)
	{
		float temp=(i-average1)*(i-average1);
		v1 += temp * histo[i];

	}
	float v2 = 0;
	for (int i = t+1 ; i<256 ; i++)
	{
		float temp =(i-average2)*(i-average2);
		v2 += temp * histo[i];

	}
	
	if (v1>v2)
	{
		return (v1-  v2);
	}
	else
	       	return v2-v1;
}

int seuil_def(float* histo)
{
	float min_ave_variance = 255 ;
	int min_index = 0;
	for (int i = 0; i <256; i++)
	{
		float ave1 = average1(histo,i);
		float ave2 = average2(histo,i);
		printf("%f %f \n",ave1,ave2);
		float ave_variance= average_variance_1_and_2(histo , i , ave1, ave2);
		
		if (ave_variance<min_ave_variance)
		{
			min_ave_variance = ave_variance;
			min_index = i;
			
		}
	}
	return min_index;
}


SDL_Surface* binarisation (char* path)
{
	SDL_Surface* gray_pict = grayscale (path);
	display_image (gray_pict);
	wait_for_keypressed();
	int seuil = seuil_def(histo_average_def(gray_pict));
	printf("%u",seuil);
	for ( int i = 0 ; i < gray_pict->w ; i++) 
	{ 
        	for (int j = 0 ; j < gray_pict->h ; j++) 
	        { 
        	    Uint32 pixelt = get_pixel(gray_pict, i , j); 
        	    Uint8 r, g, b;
		    Uint8 color; 
       		    SDL_GetRGB(pixelt, gray_pict -> format, &r, &g, &b); 
        	    if (r>=seuil)
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
    return gray_pict; 
}




int main()
{
	SDL_Surface* image_surface;
	char* path = 	("../../Ressources/image_01.jpeg");
	init_sdl();
	image_surface = binarisation(path);
 	display_image(image_surface);
	wait_for_keypressed();
	/*free( histotemp );*/
	SDL_FreeSurface(image_surface); 
	/*SDL_FreeSurface(screen_surface);*/
	

}


