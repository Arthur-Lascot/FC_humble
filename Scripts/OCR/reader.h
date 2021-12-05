#include <stdio.h>
#include <stdlib.h>

#define TRAIN_IMAGE "./Ressources/TrainingSet/train-images.idx3-ubyte"
#define TRAIN_LABEL "./Ressources/TrainingSet/train-labels.idx1-ubyte"
#define TEST_IMAGE "./Ressources/TestSet/t10k-images.idx3-ubyte"
#define TEST_LABEL "./Ressources/TestSet/t10k-labels.idx1-ubyte"

#define SIZE 784 
#define TRAIN_DATA 60000
#define TEST_DATA 10000

#define TRAIN_NUMZERO 5923
#define TEST_NUMZERO 980

//====> WITHOUT 0
#define TRAIN_DATAZ 54077
#define TEST_DATAZ 9020


#define LEN_INFO_IMAGE 4
#define LEN_INFO_LABEL 2

//First read in char
unsigned char train_char[TRAIN_DATA][SIZE];
unsigned char train_label_char[TRAIN_DATA][1];
unsigned char test_char[TEST_DATA][SIZE];
unsigned char test_label_char[TEST_DATA][1];

//Convert in double for each pixel 
double train_double[TRAIN_DATA][SIZE];
int train_label[TRAIN_DATA];
double test_double[TEST_DATA][SIZE];
int test_label[TEST_DATA];

double sudo[30][784];
double sudo_bis[27][784];

int sudo_label[30]; 
int sudo_label_bis[27];


void load_data();
