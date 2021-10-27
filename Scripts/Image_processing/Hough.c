#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "base_function_on_pict.h"
#include <math.h>
#include <stdio.h>
#include "tools.h"

int nbwhite;
int nbblack;
unsigned int* hough(SDL_Surface* image_surface)
{
	int img_w = image_surface->w; //width
	int img_h = image_surface->h; //height

	double roMax = (sqrt(img_w*img_w + img_h*img_h));
    //the biggest possible ro

	double accum_h = roMax * 2.0; //the height of the accumulator,
    //2 times ro because ro goes from -biggest to biggest

	double accum_w = 180;//the width of the accumulator, from 0 to 180 degree
	int size = (int) round(accum_h*accum_w);
	unsigned int* accum=
    (unsigned int*)calloc(size,sizeof(unsigned int));
    nbwhite = 0;
    nbblack = 0;
	//the accumulator, with calloc,
    //that create a memory gestion table
    //with a size of height * width of the accu,
    //* the size of an unsigned int

	for(int y=0;y<img_h;y+=1) //access the different pixels of the image
	{
		for(int x=0;x<img_w;x+=1)
		{
			Uint32 pixel =get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			if(r > 250 && b > 250 && g > 250)//check if it's a black pixel
			{

                nbwhite ++;
				for(int teta=0;teta<180;teta+=1)
				{
					double ro = ( ((double)x * cos((double)teta * M_PI /180) +
                    sin((double)teta * M_PI / 180) * (double)y)); 
                    //calculs of ro, formula : x*cos(teta) + y*sin(teta)
  
                    (*(accum + (int)((round(ro + roMax) * 180.0) + teta))) ++;
                    //access the right value(round of ro bring to positive
                    //*180(from a ro to another) + teta (the angle)), then
                    //add 1 to the density in this case
                }
			}
			else
			{
				nbblack++;
			}
		}
	}

    /*
    for (unsigned int i = 0 ; i < 2*(int)roMax*180.0; i++)
    {
        int p = *(accum + i);
        if (p != 0)
        {
            printf("*accum = %d\n",p);
        }
    }
    */

    printf("Check done");
    return accum;
}

SDL_Surface* hough_line(unsigned int* hough,SDL_Surface* image_surface)
{
    printf("Called hough_line\n");
    int w = image_surface->w; //width
	int h = image_surface->h; //height
    unsigned int threshold;
    if(h < w)
    {
        threshold = (int)round(w/2);
    }
    else
    {
        threshold = (int)round(h/2);
    }
	double roMax =  (sqrt(w*w + h*h));
    //((sqrt(((double)(h>w?h:w)) / 2.0)));
	double accum_h = roMax * 2.0;
	double accum_w = 180;
	int countTo4 =0;//is used to look at the 4 next
	int isFroze =0;//is used to stop the count after we reach 
    //countTo4==4 until we get a new "line with high density"
	
    List* houghList = init(); //initialisation of the list
	unsigned int currentValue; //the density of the line we are currently on
	unsigned int* dynamicPointer = hough;
    //the pointer to the line we are currently on
    //unsigned int tetabis;
    //double robis;
    /*
    for (unsigned int i = 0 ; i < 2*(int)roMax*180.0; i++)
    {
        int p = *(hough+ i);
        if (p != 0)
        {
            printf("*accum = %d\n",p);
        }
    }
    */
    for(int i=0; i<(accum_h*accum_w)-4;i++) //for each line do :
	{
		currentValue = *(dynamicPointer+i);
		//printf("%d >= 22 ==> %i\n",currentValue,currentValue>=22);
        if(currentValue>=threshold) //if density of line > threshold(22 here) :
		{
            unsigned int * p = malloc(sizeof(unsigned int));
            p[0] = i%180;
            double *q = malloc(sizeof(double));
            q[0]=(i-p[0])/180-roMax;
			//unsigned int tetabis =i%180; //teta
			//double robis = (i-tetabis)/180 - roMax;//ro
		if(countTo4==0)//if there is no other added line in the 4 last value
			{
				tuple3* temp = malloc(sizeof(*temp));
                //get the memory to stock our 3-uplet
			    if (temp==NULL)
				{
					exit(EXIT_FAILURE);
				}
				temp->item1=p;//stock teta in our 3-uplet
				temp->item2=q;//stock ro in our 3-uplet
				temp->item3=&currentValue; //stock currentValue in our 3-uplet
				//printf("added a line of density : %d\n", currentValue);
				add(houghList,temp);//Add the 3-uplet to the list
				isFroze=0;///we set up froze to false so the count can go on
			}
			else //if we already took a line in the 4 last one :
			{
				//Ifthe last line we stored had a lower density than this one :
				if((houghList->last)!=NULL || 
                (*((unsigned int*)(((tuple3*)((houghList->last)->key))->
                item3)))<currentValue) 
				{
					tuple3* temp = malloc(sizeof(*temp)); 
                    //get the memory to stock our 3-uplet
					temp->item1=p;//stock teta in our 3-uplet
					temp->item2=q;//stock ro in our 3-uplet
					temp->item3=&currentValue;//stock currentVe in our 3-uplet
					//printf("Replaced a line of density : 
                    //%d  by a line of density : %d\n",
                    //(*(unsigned int*)(((tuple3*)((houghList->last)->
                    //key))->item3)) ,currentValue);
					free(((unsigned int*)(((tuple3*)((houghList->last)->key))
                    ->item1)));
                    free(((unsigned int*)(((tuple3*)((houghList->last)->key))
                    ->item2)));
                    free(houghList->last->key);
					del(houghList); //Delete the last line we stored
					add(houghList,temp);//Add the new line
					countTo4=0; //We reset the count to 0
					isFroze=0;// And we make sure the count can go up
				}
			}
		}
		if(isFroze==0)//If he isn't froze the count can go up
		{
			countTo4++;
		}
		if (countTo4>4)
        //if the count have gone beyond 4 we froze it and setup it to 0
		{
			countTo4=0;
			isFroze=1;
		}//We go to the next line
	}
	///////////entering drawing part///////////////
	Element* currentPlace = (houghList->last);
	SDL_Surface* image_surface_temp = image_surface;
    int i = 0;
	while(currentPlace!=NULL)
	{
		tuple3* temp = currentPlace->key;
		unsigned int teta = *((unsigned int*)(temp->item1));
        double tetaR = (double)teta*M_PI/180;
		double ro = *((double*)(temp->item2));
        free(temp->item1);
        free(temp->item2);
        //printf("ro : %f\n",ro);
        int x1;
        int x2=0;
        int y1;
        int y2=0;

        if(teta == 0)
        {
            y1 = 0;
            y2 = h-1;
            x1 = (int)(ro/cos(tetaR));
            x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
        }
        else if(teta == 90)
        {
            x1 = 0;
            x2 = w-1;
            y1 = (int)(ro/sin(tetaR));
            y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
        }
        else
        {
            x1 = (int)(ro/cos(tetaR));
        if(x1 >= 0 && x1<w)
        {
            y1 = 0;
        }
        else
        {
            y1 = (int)(ro/sin(tetaR));

            if(y1>=0 && y1<h)
            {
                x1 = 0;
            }
            else
            {
                x1=(int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                y1 = h-1;
            }
        }
        if(x1 ==0)
        {
            x2 = (int)(ro/cos(tetaR));
            if(x2>=0&&x2<w)
            {
                if(x1 == x2)
                {
                    y2 = w-1;
                    y1 = 0;
                }
                else
                {
                    y2 = 0;
                    if(y1 == y2)
                    {
                        x2 = w-1;
                    }
                }
            }
            else
            {
                x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                if(x2>=0&&x2<w)
                {

                    if(x1 == x2)
                    {
                        y1 = 0;
                    }
                    
                    y2 = h-1;
                    if(y1 == y2)
                    {
                        x2 = w-1;
                    }
                }
                else
                {
                    x2 = w-1;
                    y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                }
            }
        }
        else if (y1 == 0)
        {
            y2 = (int)(ro/sin(tetaR));
            if(y2>=0&&y2<w)
            {
                if(y1 == y2)
                {
                    x1 = w-1;
                }
                x2 = 0;
            }
            else
            {
                y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                if(y2>=0&&y2<w)
                {
                    if(y1 == y2)
                    {
                        x1 = 0;
                    }
                    x2 = w-1;
                    if(x1 == x2)
                    {
                        y2 = h-1;
                    }
                }
                else
                {
                    y2 = h-1;
                    x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                }
            }

        }
        else
        {
                y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                if(y2 == y1)
                {
                    x1 = 0;
                }
                x2 = w-1;
                
            }
        }
        /*
        if(x1 == 0)
        {
            if(teta > 90 )
            {
                o = (h-y1) * tan(tetaR);
                if(o<w)
                {
                //mur bas
                    x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                    y2 = h-1;
                    if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
                else
                {
                //mur droit
                    y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                    x2 = w-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
            }
            else if (teta == 90)
            {
                x2 = x1;
                y1 = 0;
                y2 = h-1;
            }
            else
            {
                o = y1 * tan(tetaR);
                if(o<w)
                {
                //mur haut
                    x2 = (int)(ro/cos(tetaR));
                    y2 = 0;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
                else
                {
                //mur droit
                    y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                    x2 = w-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
            }
        }
        else if(y1 == 0)
        {
            if(teta > 90 )
            {
                o = (w-x1) * tan(tetaR);
                if(o<h)
                {
                //mur droit
                    y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
                    x2 = w-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
                else
                {
                //mur bas
                    x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                    y2 = h-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
            }
            else if (teta == 90)
            {
                x2 = x1;
                y2 = h-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

            }
            else
            {
                o = x1 * tan(tetaR);
                if(o<h)
                {
                //mur gauche
                    y2 = (int)o;
                    x2 = 0;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("ro = %f",ro);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
                else
                {
                //mur bas
                    x2 = (int)((ro-(h-1)*sin(tetaR))/cos(tetaR));
                    y2 = h-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

                }
            }

        }
        else
        {
            y2 = (int)((ro-(w-1)*cos(tetaR))/sin(tetaR));
           x2 = w-1;
if(x1<0 ||x1>=w||y1<0||y1>=h||x2<0||x2>w||y2<0||y2>=h)
                {
                    printf("x1 = %i",x1);
                    printf("y1 = %i",y1);
                    printf("x2 = %i",x2);
                    printf("y2 = %i",y2);
                    printf("teta = %i",teta);
                    printf("o = %f",o);
                    return image_surface;
                }

        }
        */
        /*printf("teta = %i",teta);
        printf("x2 = %i\n",x2);
        printf("y2 = %i\n",y2);
        printf("x1 = %i\n",x1);
        printf("y1 = %i\n",y1);*/
        //printf("teta = %i",teta);
		image_surface_temp = drawline(x2,y2,x1,y1,image_surface_temp);
		//printf("We drew a line");
        i+=1;
		currentPlace = currentPlace->previous;
		free(temp);
        	del(houghList);
	}
	free(hough);
	free(houghList);
	return image_surface_temp;
}
