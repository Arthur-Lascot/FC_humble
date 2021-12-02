#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

void swap(int* a,int*b);
int partition(int array[],int low,int high);
void quickSort(int array[],int low,int high);
int mean_filter(SDL_Surface* init_surface);

#endif
