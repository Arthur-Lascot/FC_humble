#include <stdio.h>
#include <math.h>


#include "forward.h"
#include "network_tools.h"
#include "reader.h"
#include "xor.h"


#define NUMINPUTS 784
#define NUMHIDNEURONS 98
#define NUMOUTPUTS 9


extern double lr;

extern int numInputs;
extern int numHidNeurons;
extern int numOutputs;

extern double hidLay[];
extern double outputLay[];
extern double hidLayBias[];
extern double outputLayBias[];
extern double hidWeights[][NUMHIDNEURONS];
extern double outputWeights[][NUMOUTPUTS];

extern double sizeTraining;

extern int training[][NUMINPUTS];

extern int target[][NUMINPUTS];  


int max_index(double output[NUMOUTPUTS])
{
    if (NUMOUTPUTS > 0)
    {
        int max_ind = 0;
        double max = output[0];
        for (int i = 0; i < NUMOUTPUTS ; i++)
        {
            if (output[i] > max)
                max_ind = i;
        }
        return max_ind;
    }
    return 0;
}

int forward(double *res,int n,int train,int test,double image[SIZE])
{
    int img = 0;
    if (train)
        img = n%TRAIN_DATA;
    else if (test)
        img = n%TEST_DATA;

    /*
       if (n%1000 == 0 && !train)
       printf("Img : %i => Label %i\n",img,test_label[img]);
     */
    /* Try solving */
    /* 
Comments : 
activation = bias + S(inputs * weights)
output : 0 if sigmoid(activation) <= 0.5
1 if sigmoid(activation) > 0.5
     */

    //First operation between input and hidden layers 
    for (int j = 0; j < numHidNeurons; j++) 
    {
        double activation = hidLayBias[j];
        for (int k = 0; k < numInputs; k++) 
        {
            if (train)
                activation += train_double[img][k] * hidWeights[k][j];
            else if (test)
                activation += test_double[img][k] * hidWeights[k][j];
            else 
                activation += image[k] * hidWeights[k][j];
        }
        hidLay[j] = sigmoid(activation);

    }

    //Second operation betwenn hidden and output layers
    double totsum = 0.0; 

    for (int j = 0; j < numOutputs; j++) 
    {
        double activation = outputLayBias[j];
        for (int k = 0; k < numHidNeurons; k++) 
        {
            activation += hidLay[k] * outputWeights[k][j];
        }
        outputLay[j] = exp(activation);
        totsum += outputLay[j];
    }

    //Softmax
    double max = outputLay[0];
    int imax = 1;
    for (int i = 0; i<numOutputs; i++)
    {
        if (outputLay[i] > max)
        {
            max = outputLay[i];
            imax = i+1;
        }
        outputLay[i] /= totsum;
    }

    *res = outputLay[imax-1];

    if (train)
    {
        if (n%1000 == 0) //|| n%1000 == 1)
        {
            if (n%3 == 1)
            {
                for (int i=0; i<784; i++) 
                {
                    if (train_double[img][i] > 0.75)
                        printf("1 ");
                    else if (train_double[img][i] > 0.5)
                        printf("  ");
                    else 
                        printf("  ");
                    if ((i+1) % 28 == 0) putchar('\n');
                }

            }

            printf("RESULT : %i => %f \n",imax,outputLay[imax-1]);
            printf("    |  Expected : %d\n",train_label[img]);
            if (n != 0)
            {
                printf("Previous : %d\n",train_label[img-1]);
                printf("Next : %d\n",train_label[img+1]);
            }

        }
        for (int j = 0 ; j < numOutputs; j++)
        {
            if (n%1000 == 0 || n%1000 == 1)
            {
                if (imax == train_label[img])
                    green();
                else
                    red();
                printf(" %i Res => %f\n",j+1,outputLay[j]);
                normal();
            }
        }
    }

    else if (test)
    {
        if (n%1000 == 0 || n%1000 == 1)
        {
            printf("RESULT : %i => %f \n",imax,outputLay[imax-1]);
            printf("    |  Expected : %d\n",test_label[img]);
            if (n != 0)
            {
                printf("Previous : %d\n",test_label[img-1]);
                printf("Next : %d\n",test_label[img+1]);
            }

        }
        for (int j = 0 ; j < numOutputs; j++)
        {
            if (n%1000 == 0 || n%1000 == 1)
            {
                if (imax == test_label[img])
                    green();
                else
                    red();
                printf(" %i Res => %f\n",j+1,outputLay[j]);
                normal();
            }
        }

    }
    else 
    {
        printf("RESULT : %i => %f \n",imax,outputLay[imax-1]);
        for (int j = 0 ; j < numOutputs; j++)
        {
            printf(" %i Res => %f\n",j+1,outputLay[j]);
        }
    }

    return imax;

}

