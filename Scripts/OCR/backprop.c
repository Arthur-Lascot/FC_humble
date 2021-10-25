#include <stdio.h>

#include "backprop.h"
#include "network_tools.h"

#define NUMINPUTS 2
#define NUMHIDNEURONS 4
#define NUMOUTPUTS 1


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

void backprop(int i,int n)
{
    //Do nothing for the moment
    int tmp = n;
    tmp++;
    
    //Calculating the delta for the outputs
    double deltaOutput[numOutputs];
    for (int j = 0; j < numOutputs; j++) 
    {
        //printf("OutputLayBACK [%i] = %f => %i\n\n"
        //,j,outputLay[j],outputLay[j] > 0.5f);
        double errorDif = (target[i][j] - outputLay[j]);
        deltaOutput[j] = errorDif * d_sigmoid(outputLay[j]);
        
        /*Print the error dif
        if (n%1000 == 0)
            printf("Error dif = %f => %d - %f\n\n",errorDif,
            target[i][j],outputLay[j]);
        */
        
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
        double errorHidden = 0.0f;
        for(int k = 0; k < numOutputs; k++) 
        {
            errorHidden += deltaOutput[k] * outputWeights[j][k];
        }
        deltaHidden[j] = errorHidden*d_sigmoid(hidLay[j]);
    }
    //Correcting the outputs with the delta
    for (int j=0; j < numOutputs; j++) 
    {
        outputLayBias[j] += deltaOutput[j]*lr;
        
        for (int k=0; k < numHidNeurons; k++) 
        {
            outputWeights[k][j] += hidLay[k] * deltaOutput[j]*lr;
            //printf("OutputWeights [%i][%i] = %f (hidLay[%f] * 
            //deltaOutput[%f]\n)",k,j,outputWeights[k][j],
            //hidLay[k],deltaOutput[j]);
        }
    }

    //Correcting the hiddens with the delta
    for (int j = 0; j < numHidNeurons; j++) 
    {
        hidLayBias[j] += deltaHidden[j]*lr;

        for(int k = 0; k < numInputs; k++) {
            hidWeights[k][j] += training[i][k] * deltaHidden[j]*lr;
        }
    }
}
