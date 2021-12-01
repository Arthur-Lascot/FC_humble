#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
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

void convert_i(int size_d,unsigned char image_char[][SIZE],
    double image[][SIZE],int label[size_d])
{
    int mnist = 0;
    int haz = 0;
    int haz_bis = 0;
    int mod = 10000;
    if (size_d == TRAIN_DATA)
        mod = 60000;
    for(int i = 0 ; i < size_d; i++)
    {
        mnist = i%mod;
        if (i%3 == 0) //1/3
        {
            for (int j = 0; j < SIZE; j++)
            {
                haz = haz%30;
                image[i][j] = sudo[haz][j];
                label[i] = sudo_label[haz];
            }
            haz++;
        }
        
        else if (i%3 == 1)
        {
            for (int j = 0; j<SIZE;j++)
            {
                haz_bis = haz_bis%27;
                image[i][j] = sudo_bis[haz_bis][j];
                label[i] = sudo_label_bis[haz_bis];
        
            }
            haz_bis++;
        }
        
        else
        {
            for (int j = 0 ; j < SIZE ;j++)
            {
                image[i][j] = (double)image_char[mnist][j]/255.0; 
            }
        }
    }
}

void convert_l(int size_d,unsigned char label_char[size_d][1],int label[size_d])
{   
    int mnist = 0;
    int mod = 10000;
    if (size_d == TRAIN_DATA)
        mod = 60000;

    for (int i = 0; i<size_d; i++)
    {
        mnist = i%mod;
        if (i%3 != 0 && i%3 != 1)
            label[i] = (int)label_char[mnist][0]; 
    }
}

void readnet(FILE *path,int size_wh,int siz,
    double arr[siz][784],int expt)
{
    double s_tmp[size_wh][784];

    for (int j = 0; j < size_wh; j++)
    {
        for (int i= 0 ;i < 784; i++)
        {
            //printf("%lf",sudo[j][i]);
            fscanf(path,"%lf\n",&s_tmp[j][i]);
        }
    }
    fclose(path);
    for (int j = 0; j < size_wh; j++)
    {

        if (expt)
        {
            if (j<12)
            {
                for (int i= 0 ;i < 784; i++)
                {
                    arr[j][i] = s_tmp[j][i];
                }
            }
            else if(j>12)
            {
                for (int i= 0 ;i < 784; i++)
                {
                    arr[j-1][i] = s_tmp[j][i];
                }
            }
        }
        else 
        {
            for (int i= 0 ;i < 784; i++)
            {
                arr[j][i] = s_tmp[j][i];
            }

        }
    }
}


void load_data()
{

    int s_label[30] = {9,5,6,1,3,7,8,6,2,9,3,5,
        //nope index = 12
        8,1,2,6,9,7,4,8,1,8,6,9,3,7,4,8,6,5};

    int s_label_bis[27] = {4,5,3,9,6,2,1,4,3,1,
    4,9,9,5,7,8,9,2,3,3,1,5,4,5,4,6,7};

    for (int i=0; i < 30;i++)
    {
        sudo_label[i] = s_label[i];
    }
    for (int i=0; i<27; i++)
    {
        sudo_label_bis[i] = s_label_bis[i];
    }

    FILE *f = fopen("../OCR/number2","r");
    FILE *f_bis = fopen("../OCR/number1","r");
    readnet(f,31,30,sudo,1);
    readnet(f_bis,27,27,sudo_bis,0);

   /* 
    for(int j =0; j<27;j++)
    {
        for (int i=0; i<784; i++) 
        {
            if (sudo_bis[j][i] > 0.75)
                printf("1 ");
            else if (sudo[j][i] > 0.5)
                printf("  ");
            else 
                printf("  ");
            if ((i+1) % 28 == 0) putchar('\n');
        }
        printf("Label => %i",sudo_label_bis[j]);
    }
    */

    //TRAIN
    read_mnist_image(TRAIN_IMAGE,TRAIN_DATA,train_char);
    read_mnist_label(TRAIN_LABEL,TRAIN_DATA,train_label_char);
    convert_i(TRAIN_DATA,train_char,train_double,train_label);
    convert_l(TRAIN_DATA,train_label_char,train_label);

    
    //TEST
    read_mnist_image(TEST_IMAGE,TEST_DATA,test_char);
    read_mnist_label(TEST_LABEL,TEST_DATA,test_label_char);
    convert_i(TEST_DATA,test_char,test_double,test_label);
    convert_l(TEST_DATA,test_label_char,test_label);
    
}





