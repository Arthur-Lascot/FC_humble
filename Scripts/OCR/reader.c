#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>


#include "reader.h"

void read_mnist_image(char *path,int size_data,unsigned char image_char[][SIZE])
{
    int f_data = open(path,O_RDONLY);

    if (f_data == -1)
        errx(1,"Cannot open the file");

    //Get the info of the file
    int info_image[LEN_INFO_IMAGE];

    read(f_data, info_image, LEN_INFO_IMAGE * sizeof(int));

    for (int i=0; i<size_data; i++) 
    {
        read(f_data, image_char[i], SIZE * sizeof(unsigned char));   
    }

    close(f_data);
}

void read_mnist_label(char *path,int size_data,unsigned char label_char[][1])
{
    int fd = open(path,O_RDONLY);

    if (fd == -1)
        errx(1,"Cannot open the file");

    //Get the info of the file
    int info_label[LEN_INFO_LABEL];

    read(fd, info_label, LEN_INFO_LABEL * sizeof(int));

    for (int i=0; i<size_data; i++) 
    {
        read(fd, label_char[i],sizeof(unsigned char));   
    }

    close(fd);
}

void convert_i(int size_d,unsigned char image_char[][SIZE],double image[][SIZE])
{
    for(int i = 0 ; i < size_d; i++)
    {
        for (int j = 0 ; j < SIZE ;j++)
        {
           image[i][j] = (double)image_char[i][j]/255.0; 
        }
    }
}

void convert_l(int size_d,unsigned char label_char[size_d][1],int label[size_d])
{
    for (int i = 0; i<size_d; i++)
    {
       label[i] = (int)label_char[i][0]; 
    }
}


void load_data()
{
    read_mnist_image(TRAIN_IMAGE,TRAIN_DATA,train_char);
    read_mnist_label(TRAIN_LABEL,TRAIN_DATA,train_label_char);
    convert_i(TRAIN_DATA,train_char,train_double);
    convert_l(TRAIN_DATA,train_label_char,train_label);
}





