#include <stdio.h>
#include "tools.h"
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
#include <math.h>
#include "square.h"

int mediane;

void quicksort(int number[],int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}

void quick_sort_custom(List* list,int temp[])
{
    Element* current = list->last;
    int i=0;
    while(current!=NULL)
    {
        temp[i]= *(unsigned int*)(((tuple3*)(current->key))->item3);
        current = current->previous;
        i++;
    }
    quicksort(temp,temp[0],temp[len(list)-1]);
}
List* square_column(SDL_Surface* image_surface)
{
    int x = 0;
    int y = 0;
    int i = 1;
    int l = 0;
    int right = 0;
    int oof = 0;
    List* dist = init();
    int w = image_surface->w;
    int h = image_surface->h;
    int ec_type;
    if(w>h)
    {
        ec_type = (int)round(w/100);
    }
    else
    {
        ec_type = (int)round(h/100);
    }
    Uint32 pixel;
    Uint8 r,g,b;
    pixel = get_pixel(image_surface,x,y);
    SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
    do{
        oof =0;
        while (!(g==255 && r==0 && b == 0))
        {
            pixel = get_pixel(image_surface,x,y);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            x++;
            if(x == w)
            {
                x = 0;
                y +=1;
            }
        }
        i = x;
        while(i<ec_type&&(g == 255&&r==0&&b==0))
        {
            pixel = get_pixel(image_surface,i,y);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            i++;
            if(i == ec_type)
            {
                y += 1;
                i = x;
                pixel = get_pixel(image_surface,i,y);
                SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                if(r!=0||g!=255||b!=0)
                {
                    x = 0;
                    oof = 1;
                }
            }
        }
    }while(oof == 1);
    l = x;
    right=x+1;
    //
    while(right<w)
    {
        int *leftp = malloc(sizeof(int));
        int *rightp = malloc(sizeof(int));
        int *distancep=malloc(sizeof(int));
        rightp[0]=right;
        pixel = get_pixel(image_surface,right,y);
        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
        while(g!=255||r!=0||b!=0)
        {
            rightp[0]++;
            if(rightp[0]==w)
            {
                rightp[0]-=1;
                break;
            }
            pixel = get_pixel(image_surface,rightp[0],y);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
        }
        leftp[0]=l;
        distancep[0] = rightp[0]-1-leftp[0];
        tuple3* ecart = malloc(sizeof(*ecart));
        ecart->item1 = leftp;
        ecart->item2 = rightp;
        ecart->item3 = distancep;
        add(dist,ecart);
        l = rightp[0];
        right=rightp[0]+1;
    }
    List* ecart_clean = init();
    Element* current_ecart = dist->last;
    while(current_ecart!=NULL)
    {
        if(*((int*)(((tuple3*)(current_ecart->key))->item3))>ec_type)
        {
            add(ecart_clean,current_ecart->key);
        }
        else
        {
        free((int*)(((tuple3*)(current_ecart->key))->item3));
        free((int*)(((tuple3*)(current_ecart->key))->item2));
        free((int*)(((tuple3*)(current_ecart->key))->item1));
        free(((tuple3*)(current_ecart->key)));
        }
        current_ecart = current_ecart->previous;
        del(dist);
    }
    free(dist); 
    ////////////////////////////
    //sort(ecart_clean_copie);
    ////////////////////////////
    int temp[len(ecart_clean)];
    quick_sort_custom(ecart_clean,temp);
    int median = temp[len(ecart_clean)/2];
    List* result = init();
    current_ecart = ecart_clean->last;
    Element* neighbour_ecart = ecart_clean->last;
    int compteur = 0;
    while(neighbour_ecart!=NULL&&compteur<9)
    {
        if(neighbour_ecart==current_ecart)
        {
            int value = *((int*)(((tuple3*)(current_ecart->key))->item3));
            if(value<median+ec_type&&value>median-ec_type)
            {

                neighbour_ecart = neighbour_ecart->previous;
                compteur +=1;
            }
            else
            {
                
                free((int*)(((tuple3*)(current_ecart->key))->item3));
                free((int*)(((tuple3*)(current_ecart->key))->item2));
                free((int*)(((tuple3*)(current_ecart->key))->item1));
                free(((tuple3*)(current_ecart->key)));
                current_ecart = current_ecart->previous;
                neighbour_ecart = neighbour_ecart->previous;
                del(ecart_clean);
            }
        }
        else
        {
	    if(neighbour_ecart==NULL){errx(1,"neighbour ==NULL");}
            int value = *((int*)(((tuple3*)(neighbour_ecart->key))->item3));
            if(value<median+ec_type&&value>median-ec_type)
            {

                neighbour_ecart = neighbour_ecart->previous;
                compteur +=1;
            }
            else
            {
                neighbour_ecart = neighbour_ecart->previous;
                while(current_ecart!=neighbour_ecart)
                {

                    free((int*)(((tuple3*)(current_ecart->key))->item3));
                    free((int*)(((tuple3*)(current_ecart->key))->item2));
                    free((int*)(((tuple3*)(current_ecart->key))->item1));
                    free(((tuple3*)(current_ecart->key)));
                    current_ecart = current_ecart->previous;
                    del(ecart_clean);
                }
                compteur = 0;
            }
        }
    }
    if(compteur != 9)
        {
            errx(1,"you didn't detect a sudoku (column)");
        }
        else
        {
            while(current_ecart!=neighbour_ecart)
            {
                add(result,current_ecart->key);
                current_ecart=current_ecart->previous;
                del(ecart_clean);
            }
            while(current_ecart!=NULL)
            {

                free((int*)(((tuple3*)(current_ecart->key))->item3));
                free((int*)(((tuple3*)(current_ecart->key))->item2));
                free((int*)(((tuple3*)(current_ecart->key))->item1));
                free(((tuple3*)(current_ecart->key)));
                current_ecart = current_ecart->previous;
                del(ecart_clean);
            }
    }
    
    free(ecart_clean);
    return result;
}

//je te laisse ça là
//toutes les keys->arrays
//quicksort
//tu as ta key, tu cherches ta list avec la meme key
//sale, mais efficace

List* square_line(SDL_Surface* image_surface)
{
    int x = 0;
    int y = 0;
    int i = 1;
    int high = 0;
    int low = 0;
    int oof = 0;
    List* dist = init();
    int h = image_surface->h;
    int w = image_surface->w;
    int ec_type;
    if(w>h)
    {
        ec_type = (int)round(w/100);
    }
    else
    {
        ec_type = (int)round(h/100);
    }

    Uint32 pixel;
    Uint8 r,g,b;
    pixel = get_pixel(image_surface,x,y);
    SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
    do{
        oof =0;
        while (!(g==255 && r==0 && b == 0))
        {
            pixel = get_pixel(image_surface,x,y);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            y++;
            if(y == h)
            {
                y = 0;
                x +=1;
            }
        }
        i = y;
        while(i<ec_type&&(g == 255&&r==0&&b==0))
        {
            pixel = get_pixel(image_surface,x,i);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
            i++;
            if(i == ec_type)
            {
                x += 1;
                i = y;
                pixel = get_pixel(image_surface,x,i);
                SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
                if(r!=0||g!=255||b!=0)
                {
                    y = 0;
                    oof = 1;
                }
            }
        }
    }while(oof == 1);
    high = y;
    low=y+1;
    //switch left -> high, right -> low, x-> y 
    while(low<h)
    {
        int *highp = malloc(sizeof(int));
        int *lowp = malloc(sizeof(int));
        int *distancep=malloc(sizeof(int));
        lowp[0]=low;
        pixel = get_pixel(image_surface,x,low);
        SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
        while(g!=255||r!=0||b!=0)
        {
            lowp[0]++;
            if(lowp[0]==h)
            {
                lowp[0]-=1;
                break;
            }
            pixel = get_pixel(image_surface,x,lowp[0]);
            SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
        }
        highp[0]=high;
        distancep[0] = lowp[0]-1-highp[0];
        tuple3* ecart = malloc(sizeof(*ecart));
        ecart->item1 = highp;
        ecart->item2 = lowp;
        ecart->item3 = distancep;
        add(dist,ecart);
        high = lowp[0];
        low=lowp[0]+1;
    }
    List* ecart_clean = init();
    Element* current_ecart = dist->last;
    while(current_ecart!=NULL)
    {
        if(*((int*)(((tuple3*)(current_ecart->key))->item3))>ec_type)
        {
            add(ecart_clean,current_ecart->key);
        }
        else
        {
        free((int*)(((tuple3*)(current_ecart->key))->item3));
        free((int*)(((tuple3*)(current_ecart->key))->item2));
        free((int*)(((tuple3*)(current_ecart->key))->item1));
        free(((tuple3*)(current_ecart->key)));
        }
        current_ecart = current_ecart->previous;
        del(dist);
    }
    free(dist);
    ///////////////////////////
    //sort(ecart_clean_copie);
    ///////////////////////////
    int temp[len(ecart_clean)];
    quick_sort_custom(ecart_clean,temp);
    int median = temp[len(ecart_clean)/2];
    List* result = init();
    current_ecart = ecart_clean->last;
    Element* neighbour_ecart = ecart_clean->last;
    int compteur = 0;    
    while(neighbour_ecart!=NULL&&compteur<9)
    {
        if(neighbour_ecart==current_ecart)
        {
            int value = *((int*)(((tuple3*)(current_ecart->key))->item3));
            if(value<median+ec_type&&value>median-ec_type)
            {
                neighbour_ecart = neighbour_ecart->previous;
                compteur +=1;
            }
            else
            {
                free((int*)(((tuple3*)(current_ecart->key))->item3));
                free((int*)(((tuple3*)(current_ecart->key))->item2));
                free((int*)(((tuple3*)(current_ecart->key))->item1));
                free(((tuple3*)(current_ecart->key)));
                current_ecart = current_ecart->previous;
                neighbour_ecart = neighbour_ecart->previous;
                del(ecart_clean);
            }
        }
        else
        {
            int value = *((int*)(((tuple3*)(neighbour_ecart->key))->item3));
            if(value<median+ec_type&&value>median-ec_type)
            {
                neighbour_ecart = neighbour_ecart->previous;
                compteur +=1;
            }
            else
            {
                neighbour_ecart = neighbour_ecart->previous;
                while(current_ecart!=neighbour_ecart)
                {
                    free((int*)(((tuple3*)(current_ecart->key))->item3));
                    free((int*)(((tuple3*)(current_ecart->key))->item2));
                    free((int*)(((tuple3*)(current_ecart->key))->item1));
                    free(((tuple3*)(current_ecart->key)));
                    current_ecart = current_ecart->previous;
                    del(ecart_clean);
                }
                compteur = 0;
            }
        }
    }
        if(compteur != 9)
        {
            errx(1,"you didn't detect a sudoku (line)");
        }
        else
        {
            while(current_ecart!=neighbour_ecart)
            {
                add(result,current_ecart->key);
                current_ecart=current_ecart->previous;
                del(ecart_clean);
            }
            while(current_ecart!=NULL)
            {
                free((int*)(((tuple3*)(current_ecart->key))->item3));
                free((int*)(((tuple3*)(current_ecart->key))->item2));
                free((int*)(((tuple3*)(current_ecart->key))->item1));
                free(((tuple3*)(current_ecart->key)));
                current_ecart = current_ecart->previous;
                del(ecart_clean);
            }
        }
    free(ecart_clean);
    return result;
}

SDL_Surface* DrawSquare(SDL_Surface* image_surface,List* column,List* line)
{
    Element* current_column = column->last;
    Element* current_line;
    Uint32 red = SDL_MapRGB(image_surface->format,255,0,0);
    while(current_column != NULL)
    {
        int left = *((int*)(((tuple3*)(current_column->key))->item1));
        int right = *((int*)(((tuple3*)(current_column->key))->item2));
        current_line = line->last;
        while(current_line != NULL)
        {
            int high = *((int*)(((tuple3*)(current_line->key))->item1));
            int low = *((int*)(((tuple3*)(current_line->key))->item2));
            for(int i = high;i<low;i++)
            {
                put_pixel(image_surface,left,i,red);
                put_pixel(image_surface,right,i,red);
            }
            for(int j = left;j<right;j++)
            {
                put_pixel(image_surface,j,high,red);
                put_pixel(image_surface,j,low,red);
            }
            current_line = current_line->previous;
        }
        free((int*)(((tuple3*)(current_column->key))->item1));
        free((int*)(((tuple3*)(current_column->key))->item2));
        free((int*)(((tuple3*)(current_column->key))->item3));
        free(current_column->key);
        current_column = current_column->previous;
        del(column);
    }
    current_line = line->last;
    while(current_line!=NULL)
    {
        free((int*)(((tuple3*)(current_line->key))->item1));
        free((int*)(((tuple3*)(current_line->key))->item2));
        free((int*)(((tuple3*)(current_line->key))->item3));
        free(current_line->key);
        current_line = current_line->previous;
        del(line);
    }
    free(column);
    free(line);
    int w = image_surface->w;
    int h = image_surface->h;
    Uint32 black = SDL_MapRGB(image_surface->format,0,0,0);
    for (int i =0;i<w;i++)
    {
	    for(int j=0;j<h;j++)
	    {
		    Uint32 pixel;
		    Uint8 r,g,b;
		    pixel = get_pixel(image_surface,i,j);
		    SDL_GetRGB(pixel,image_surface->format,&r,&g,&b);
		    if(r==0 && g==255 && b==0)
		    {
			    put_pixel(image_surface,i,j,black);
		    }
	    }
    }
    return image_surface;
}

