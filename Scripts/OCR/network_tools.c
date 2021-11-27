#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "network_tools.h"

//Color
void red () 
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[0;32m");
}

void normal()
{
    printf("\033[0m");
}

//Length of a string
int lenstr(char string[])
{
    int i =0;
    while (string[i] != 0)
    {
        i++;
    }
    return i;
}


//Sigmoid function
double sigmoid(double d)
{
    double ed = exp(-d);
    double res = 1 / (1 + ed);
    return res;
}
//Derivative
double d_sigmoid(double d)
{
    double res = sigmoid(d) * (1-sigmoid(d));
    return res;
}


