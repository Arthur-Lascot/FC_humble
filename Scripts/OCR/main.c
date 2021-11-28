#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "xor.h"
#include "reader.h"


int main(int argc,char** argv)
{
    //====> Initialization <====//
    if (argc != 2)
        errx(1,"Usage: path");

    char *path = argv[1]; 

    FILE *filenet = fopen(path,"r");

    int reading = 1; //Reading or Writing a file
        if (filenet == NULL)
    {
        filenet = fopen(path,"w");
        reading = 0;
        if (filenet == NULL)
            errx(1,"Error : Could not write the network file");
    }

    xr(reading,filenet,NULL);

}
