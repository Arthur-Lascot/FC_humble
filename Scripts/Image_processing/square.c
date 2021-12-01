#include <stdio.h>
#include "tools.h"
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_rotozoom.h>
#include "base_function_on_pict.h"
#include <math.h>
#include <string.h>
#include "square.h"

#include "../OCR/xor.h"

int mediane;
extern char sudoku[];


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
    quicksort(temp,/*temp[0]*/0,/*temp[*/len(list)-1/*]*/);
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
    int ec2_type;
    if(w>h)
    {
        ec_type = (int)round(w/100);
        ec2_type = (int)round(w/200);
    }
    else
    {
        ec_type = (int)round(h/100);
        ec2_type = (int)round(h/200);
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
            if(value<median+ec2_type&&value>median-ec2_type)
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
    int ec2_type;
    if(w>h)
    {
        ec_type = (int)round(w/100);
        ec2_type = (int)round(w/200);
    }
    else
    {
        ec_type = (int)round(h/100);
        ec2_type = (int)round(h/200);
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
            {
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
        }}while(oof == 1);
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
            if(value<median+ec2_type&&value>median-ec2_type)
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

void fillHole(double* dst)
{
    double acc =0;
    int neighbours = 0;
    for(int i=28;i<27*27;i+=28)
    {
        for(int j=1;j<27;j++)
        {
            
            if(dst[i+28+j]>=0.3)
            {
                acc+=dst[i+28+j];
                neighbours++;
            }
            if(dst[i-28+j]>=0.3)
            {
                acc+=dst[i+28+j];
                neighbours++;
            }
            if(dst[i+j+1]>=0.3)
            {
                acc+=dst[i+j+1];
                neighbours++;
            }
            if(dst[i+j-1]>=0.3)
            {
                acc+=dst[i+j-1];
                neighbours++;
            }
            
             
            if(neighbours>=3)
            {
                dst[i+j] = acc/neighbours;
            }
            
            //dst[i+j] = neighbours*0.20;
            
            neighbours = 0;
            acc=0;
        }
    }
    for(int i=0;i<28;i++)
    {
	    dst[i]=0;
    }
    for(int i=0;i<28*28;i+=28)
    {
	    dst[i]=0;
    }
    for(int i=27;i<28*28;i+=28)
    {
	    dst[i]=0;
    }
}

void adjust(double *dst)
{
    int neighbours = 0;
    for(int i=28;i<27*27;i+=28)
    {
        for(int j=1;j<27;j++)
        {
            
            if(dst[i+28+j]>=0.3)
            {
                neighbours++;
            }
            if(dst[i-28+j]>=0.3)
            {
                neighbours++;
            }
            if(dst[i+j+1]>=0.3)
            {
                neighbours++;
            }
            if(dst[i+j-1]>=0.3)
            {
                neighbours++;
            }
            
             
            if(neighbours>=3)
            {
                dst[i+j] = 0.80;
            }
            
            //dst[i+j] = neighbours*0.20;
            
            neighbours = 0;
        }
    }
}


int format(SDL_Surface* src,double* dst)
{
    int res =0;
    double moy = 0;
    int i = 0;
    int j =0;
    int m = 3;
    printf("\nDim %i/%i \n",src->w,src->h);
    while(j<112*112 && m<112)
    {
        for(int k=0;k<4;k++)
        {
            for(int l=0;l<4;l++)
            {
                Uint32 pixel;
                Uint8 r,g,b;
                //printf(" %i/%i ",j%112,m+(-3+l));
                pixel = get_pixel(src,j%112,m +(-3+l));
                SDL_GetRGB(pixel,src->format,&r,&g,&b);
                if(r!=255||g!=255||b!=255)
                {
                    moy +=0;
                }
                else
                {
                    //printf("there is a one\n");
                    moy+=1;
                }
            }
            j++;
        }
        if(j%112==0){m +=4;}
        moy/=(4*4);
        if(moy!=0)
        {
            res = 1;
            /*
            moy *= 2;
            if (moy > 1)
                moy = 1;
            */
            
            if (moy>0.10 && moy < 0.70) 
            {
                moy+=0.30;
                //printf("%f\n",moy);
            }
            
            else if (moy >= 0.70) 
            {
                moy = 1;
                //printf("%f\n",moy);
            }
            
        }
        dst[i]=moy;
        moy =0;
        i++;
    }
    for (int j = 0; j <28*28;j++)
    {
        adjust(dst);
    }
    return res;
}


void writenet(FILE *path,double sudo[31][784],int num[31])
{
    for (int j = 0; j < 31; j++)
    {
        if (num[j] != 0)
        {
            for (int i= 0 ;i < 784; i++)
            {
                //printf("%lf",sudo[j][i]);
                fprintf(path,"%lf\n",sudo[j][i]);
            }
        }
    }

    fclose(path);
}



SDL_Surface* DrawSquare(SDL_Surface* image_surface,List* column,List* line)
{
    Element* current_column = column->last;
    Element* current_line;
    Uint32 red = SDL_MapRGB(image_surface->format,255,0,0);
    Uint32 black = SDL_MapRGB(image_surface->format,0,0,0);
    int i = -1;
    int isNotBlank = 0;
    /*
    FILE *f = fopen("number2","w");
    double sudo[81][784];
    int num[81];
    int c = 0;
    */
    while(current_column != NULL)
    {
        int left = *((int*)(((tuple3*)(current_column->key))->item1));
        int right = *((int*)(((tuple3*)(current_column->key))->item2));
        current_line = line->last;
        while(current_line != NULL)
        {
            i++;
            int high = *((int*)(((tuple3*)(current_line->key))->item1));
            int low = *((int*)(((tuple3*)(current_line->key))->item2));
            SDL_Rect square;
            square.x = left+4;
            square.y = high+4;
            square.h = low - high -4;
            square.w = right - left -4;
            SDL_Surface* newImage = SDL_CreateRGBSurface(0,square.w,square.h
                    ,32,0,0,0,0);
            if(SDL_BlitSurface(image_surface,&square,newImage,NULL)==0){
                double zoomx = 112/(double) newImage->w;
                double zoomy = 112/(double) newImage->h;
                SDL_Surface* image112x112 = zoomSurface(newImage,zoomx,zoomy,0);
                double* Case = calloc(28*28,sizeof(double));
                isNotBlank= format(image112x112,Case);


                if(isNotBlank==1){
                    isNotBlank=0;

                        
                    for (int i=0; i<784; i++) 
                    {
                        if (Case[i] > 0.75)
                            printf("1 ");
                        else if (Case[i] > 0.5)
                            printf("0 ");
                        else 
                            printf("  ");
                        if ((i+1) % 28 == 0) putchar('\n');
                    }

                    sudoku[i] = (char)xr(1,NULL,Case);
                    display_image(image112x112);
                    wait_for_keypressed();
                    /*
                    for(int h = 0;h < 784; h++)
                    {
                        sudo[c][h] = Case[h];
                    }
                    num[c] = sudoku[i];
                    c++;
                    */
                }
                else{
                    //printf("I=%i\n",i);
                    sudoku[i]='0';
                }
                
                SDL_FreeSurface(image112x112);
                free(Case);
            }
            SDL_FreeSurface(newImage);
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
    
    /*
    if (num[1] != 0)
    {
        printf("Not 0");
        for (int j = 0; j<784;j++)
        {
            printf("%lf",sudo[1][j]);
        }
    }
    */
    //writenet(f,sudo,num);
   
    return image_surface;
}
