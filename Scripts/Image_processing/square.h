#ifndef SQUARE_H
#define SQUARE_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include "tools.h"

void quicksort(int number[],int first,int last);
void quick_sort_custom(List* list,int temp[]);
List* square_column(SDL_Surface* image_surface);
List* square_line(SDL_Surface* image_surface);
void DrawSquare(SDL_Surface* image_surface,List* column, List* line);

#endif
