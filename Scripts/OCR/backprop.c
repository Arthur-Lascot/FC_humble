#include <stdio.h>

#include "backprop.h"
#include "network_tools.h"
#include "reader.h"
//#include "xor.h"


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

double errorOut[NUMOUTPUTS];
double errorHid[NUMHIDNEURONS];

double deltaOS[NUMHIDNEURONS][NUMOUTPUTS];
double deltaHS[NUMINPUTS][NUMHIDNEURONS];

/* BackPropagation */
/*
Parameters : 
    int i => set of training and target
    int n => generation number

Comments :
errorDif : (targeted - output)
deltaOutput = MSE for each output neurons
deltaHidden = MSE for each hidden neurons
 */

void backprop(int n)
{
    
    int img = n%TRAIN_DATA;
    //Calculating the delta for the outputs
    double deltaOutput[numOutputs];
    double rerror = 0.0;
    
    for (int j = 0; j < numOutputs; j++) 
    {
        double expected = 0.0;
        if (j+1 == train_label[img])
        {
            if (n%1000 == 0)
                printf("=>BackProp Input : (j)%i => (expected)%i\n",j+1,train_label[img]);
            expected = 1.0;
        }
        //printf("OutputLayBACK [%i] = %f => %i\n\n"
        errorOut[j] = (expected - outputLay[j]);
        deltaOutput[j] = (-errorOut[j]) * d_sigmoid(outputLay[j]);
        /*
        if (n%1000 == 0)
            printf("DELTA OUTPUT[%i] = %f\n",j,deltaOutput[j]);
        */
        rerror += errorOut[j]*errorOut[j];

        //Print the error dif
        if (n%1000 == 0)
            printf("Error dif = %f => %f - %f\n",errorOut[j],expected,outputLay[j]);
        
        
        /*Result Good enough
        if (errorDif <= 0.10f && errorDif >= -0.10f)
        {
            *endTrain += 1;
        }*/
    }

    //Calculating the delta for the hiddens
    double deltaHidden[numHidNeurons];
    for (int j = 0; j < numHidNeurons; j++) 
    {
        errorHid[j] = 0.0;
        for(int k = 0; k < numOutputs; k++) 
        {
            errorHid[j] += deltaOutput[k] * outputWeights[j][k];
        }
        deltaHidden[j] = errorHid[j]* d_sigmoid(hidLay[j]);
        //(1.0+hidLay[j])*(1.0-hidLay[j]);     
  }
    //Correcting the outputs with the delta
    for (int j=0; j < numOutputs; j++) 
    {
        outputLayBias[j] += deltaOutput[j]*lr;
        
        for (int k=0; k < numHidNeurons; k++) 
        {
            deltaOS[k][j] = hidLay[k] * deltaOutput[j]*lr;//+deltaOS[k][j]*lr;
            outputWeights[k][j] -= deltaOS[k][j]; 
            //printf("OutputWeights [%i][%i] = %f (hidLay[%f] * 
            //deltaOutput[%f]\n)",k,j,outputWeights[k][j],
            //hidLay[k],deltaOutput[j]);
        }
    }

    //Correcting the hiddens with the delta
    for (int j = 0; j < numHidNeurons; j++) 
    {
        hidLayBias[j] += deltaHidden[j]*lr;
        /*
        if (n%1000 == 0)
        {
            printf("  HidLayBias[%i] : %f with deltaH : %f ",j,hidLayBias[j],deltaHidden[j]);
        }
        */
        for(int k = 0; k < numInputs; k++)
        {
            deltaHS[k][j]=train_double[img][k]*deltaHidden[j]*lr;//+deltaHS[k][j]*lr;
            hidWeights[k][j] -= deltaHS[k][j];
            /*
            if (n%1000 == 0 && k == 0 && j <10)
            {
                printf("Change hidweights[%i][%i] => %f",k,j,)
            }
            */
        }
    }
}
