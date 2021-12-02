#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
#include <stdio.h>

// function to swap elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
} 



int mean_filter(SDL_Surface* init_surface)
{
    int width = init_surface->w;
    int height = init_surface->h;

    SDL_Surface* image_surface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_BlitSurface(init_surface,NULL,image_surface,NULL);
    Uint8 r,g,b;
    int nb_value = 0;
    int new_value = 0;
    int M[9];
    int x = 0;
    Uint32 pixel;
    for(int i = 0;i<2;i++)
    {
        for(int j = 0;j<2;j++)
        {
            pixel = get_pixel(init_surface,i,j);
            SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
            M[x]= r;
            x++;
            nb_value ++;
        }
    }
    quickSort(M,0,nb_value-1);
    new_value = M[nb_value/2];
    pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
    put_pixel(image_surface,0,0,pixel);
    nb_value = 0;
    x = 0;
    for(int j = 1;j<height-1;j++)
    {
        for(int k = -1;k<2;k++)
        {
            for(int i = 0;i<2;i++)
            {
                pixel = get_pixel(init_surface,i,j+k);
                SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
                M[x]= r;
                x++;
                 nb_value ++;
            }
        }
        quickSort(M,0,nb_value-1);
        new_value = M[nb_value/2];
        pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
        put_pixel(image_surface,0,j,pixel);
        nb_value = 0;
        x=0;
    }
    for(int i = 0;i<2;i++)
    {
        for(int j = -1;j<1;j++)
        {
            pixel = get_pixel(init_surface,i,height-1+j);
            SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
            M[x] = r;
            x++;
            nb_value ++;
        }
    }
    quickSort(M,0,nb_value-1);
    new_value = M[nb_value/2];
    pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
    put_pixel(image_surface,0,height-1,pixel);
    nb_value = 0;
    x =0;
    for(int i = 1;i<width-1;i++)
    {
        for(int j = 0;j<height;j++)
        {
            for(int k = -1;k<2;k++)
            {
                if(j == 0)
                {
                    for(int l = 0;l<2;l++)
                    {
                        pixel = get_pixel(init_surface,i+k,j+l);
                        SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
                        M[x]= r;
                        x++;
                        nb_value ++;
                    }
                }
                else if(j == height-1)
                {
                    for(int l = -1;l<1;l++)
                    {
                        pixel = get_pixel(init_surface,i+k,j+l);
                        SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
                        M[x] = r;
                        x++;
                        nb_value ++;
                    }
                }
                else
                {
                    for(int l = -1;l<2;l++)
                    {
                        pixel = get_pixel(init_surface,i+k,j+l);
                        SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
                        M[x] = r;
                        x++;
                        nb_value ++;
                    }
                }
            }
            quickSort(M,0,nb_value-1);
            new_value = M[nb_value/2];
            pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
            put_pixel(image_surface,i,j,pixel);
            nb_value = 0;
            x = 0;
        }
    }
    for(int i = -1;i<1;i++)
    {
        for(int j = 0;j<2;j++)
        {
            pixel = get_pixel(init_surface,width-1+i,j);
            SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
            M[x] = r;
            x++;
            nb_value ++;
        }
    }
    quickSort(M,0,nb_value-1);
    new_value = M[nb_value/2];
    pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
    put_pixel(image_surface,width-1,0,pixel);
    nb_value = 0;
    x = 0;
    for(int j = 1;j<height-1;j++)
    {
        for(int k = -1;k<2;k++)
        {
            for(int i = -1;i<1;i++)
            {
                pixel = get_pixel(init_surface,width-1+i,j+k);
                SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
                M[x]= r;
                x++;
                nb_value ++;
            }
        }

        quickSort(M,0,nb_value-1);
        new_value = M[nb_value/2];
        pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
        put_pixel(image_surface,width-1,j,pixel);
        nb_value = 0;
        x= 0;
    }
    for(int i = -1;i<1;i++)
    {
        for(int j = -1;j<1;j++)
        {
            pixel = get_pixel(init_surface,width-1+i,height-1+j);
            SDL_GetRGB(pixel,init_surface->format,&r,&g,&b);
            M[x]= r;
            x++;
            nb_value ++;
        }
    }
    quickSort(M,0,nb_value-1);
    new_value = M[nb_value/2];
    pixel = SDL_MapRGB(image_surface->format,new_value,new_value,new_value);
    put_pixel(image_surface,width-1,height-1,pixel);
    nb_value = 0;
    x = 0;
    SDL_BlitSurface(image_surface,NULL,init_surface,NULL);
    SDL_FreeSurface(image_surface);

    return 0;
}
