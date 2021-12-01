#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
//out : empty list
List* init()
{
	List *list = malloc(sizeof(*list));
	if (list==NULL)
	{
		exit(EXIT_FAILURE);
	}
	list->first = NULL; //initilisation of first
	list->last = NULL; //initilisation of last
	return list;
}

//Add an element at the end of the list
//Entry : 1 - List* (the pointer of your list)
//        2 - Void* (the pointer of the value you want to add)
//Exampple : you want to add the int 3 to your list 
// int myNumber = 3; 
// add(myList,&myNumber)
//Out : void
void add(List* list, void* newKey)
{
	if(list->first==NULL) //if the list is empty
	{
		//We give memory for the new element
		Element* new = malloc(sizeof(*new));
		if (list == NULL || new == NULL)
		{
			exit(EXIT_FAILURE);
		}
		//then first and last should point to the new element
		list->first = new;
		list->last = new;
		new->key = newKey; //the address of the value of the element
		new->next = NULL; 
		new->previous = NULL;
	}
	else
	{
		//We give memory for the new element
		Element* new = malloc(sizeof(*new));
		if(list == NULL || new == NULL)
		{
			exit(EXIT_FAILURE);
		}
		(list->last)->next=new; //the last element now point to the new element
		new->previous=list->last;
		list->last = new;//then the new element become the last element
		new->key = newKey; //the address of the value of the element
		new->next = NULL;
		
	}
}

//delete the first element of the list 
//Entry : *List (your list)
void del (List *list)
{
	if(list == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (list->last != NULL)
	{
		Element* toFree = list->last;
		list->last = (list->last)->previous;
		free(toFree);
	}
}

int len (List *list)
{
	int acc =0;
	if (list==NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element* current = list->first;
	while(current!=NULL)
	{
		acc++;
		current = current->next;
	}
	return acc;
}
//////////////////////////////////////////////////////////////////
///////////////////////// LIST PART END HERE ////////////////////
////////////////////////////////////////////////////////////////

void drawline(int x1,int y1,int x2,int y2,SDL_Surface* image_surface)
{
	int dx = x2-x1;
	int dy = y2-y1;
	int y = y1;
	double error = 0.0;
    int z= 1;
    if(dy<0)
    {
        z = -1;
    }
    int t = 1;
    if(x1>x2){
        t = -1;
    }
    if(dy == 0)
    {
        for(int i = x1; i!=x2; i+=t)
        {
            Uint32 greenPixel = SDL_MapRGB(image_surface->format,0,255,0);
            put_pixel(image_surface,i,y1,greenPixel);

        }
    }
    if(dx == 0)
    {
        for(int i = y1;i!=y2;i+=z)
        {
            Uint32 greenPixel = SDL_MapRGB(image_surface->format,0,255,0);
            put_pixel(image_surface,x1,i,greenPixel);
        }
    }

	double current = dy/dx;
	double previous = -1.0;
    	for(int x=x1; x!=x2; x+=t)
	{
		Uint32 greenPixel = SDL_MapRGB(image_surface->format,0,255,0);
        //printf("Put_Pixerl (x) : %i\n",x);
        //printf("Put_Pixerl (y) : %i\n",y);
		put_pixel(image_surface, x, y, greenPixel); 
		error += current;
		if (error>=0.5)
		{
            
			y+=z;
			error+= previous;
		}
	}
}

