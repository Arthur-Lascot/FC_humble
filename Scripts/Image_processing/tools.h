#ifndef TOOLS_H
#define TOOLS_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
typedef struct tuple3 tuple3;
struct tuple3
{
	void* item1;
	void* item2;
	void* item3;
};

typedef struct Element Element;
struct Element
{
	void* key;
	Element* next;
	Element* previous;
};

typedef struct List List;
struct List
{
	Element *first;
	Element *last;
};

List* init();
void add(List* list, void* newKey);
void del (List *list);
int len (List *list);
void drawline(int x1,int y1,int x2,int y2,SDL_Surface* image_surface);	

#endif
