#include <stdio.h>
#include <math.h>


#include "forward.h"
#include "network_tools.h"
#include "reader.h"
//#include "xor.h"


#define NUMINPUTS 784
#define NUMHIDNEURONS 64
#define NUMOUTPUTS 10


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

int forward(int i,int n)
{
    int img = n%60000;
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
            activation += train_double[img][k] * hidWeights[k][j];
            //activation += training[i][k] * hidWeights[k][j];
        }
        hidLay[j] = sigmoid(activation);

        //Print the hidden layer
        /*
           if (n%1000 == 0)
           printf("HidLay [%i] = %f\n",j,hidLay[j]);
         */
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

    /*
    //Second operation betwenn hidden and output layers
    for (int j = 0; j < numOutputs; j++) 
    {
    double activation = outputLayBias[j];
    for (int k = 0; k < numHidNeurons; k++) 
    {
    activation += hidLay[k] * outputWeights[k][j];
    }
    outputLay[j] = sigmoid(activation);

    if (n%1000 == 0)
    {
    double varOut = outputLay[j];
    if ((varOut > 0.5f) == target[i][j])
    green();
    else
    red();
    printf("%f => %i",varOut,varOut > 0.5f);
    printf(" | Expected : %i\n",target[i][j]);
    normal();
    }
    }

    double max = outputLay[0];
    int imax = 0;
    for (int i = 0; i<numOutputs; i++)
    {
    if (outputLay[i] > max)
    {
    max = outputLay[i];
    imax = i;
    }
    }
     */


    //Softmax
    double max = outputLay[0];
    int imax = 0;
    for (int i = 0; i<numOutputs; i++)
    {
        if (outputLay[i] > max)
        {
            max = outputLay[i];
            imax = i;
        }
        outputLay[i] /= totsum;
    }

    if (n%1000 == 0 || n%1000 == 1)
    {
        printf("RESULT : %i => %f \n",imax,outputLay[imax]);
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
            printf(" %i Res => %f\n",j,outputLay[j]);
            normal();
        }
    }
    return imax;

}

