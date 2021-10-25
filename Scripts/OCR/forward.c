#include <stdio.h>

#include "forward.h"
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

void forward(int i,int n)
{
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
                    activation += training[i][k] * hidWeights[k][j];
                }
                hidLay[j] = sigmoid(activation);
                
                //Print the hidden layer
                /*
                if (n%1000 == 0)
                    printf("HidLay [%i] = %f\n",j,hidLay[j]);
                */
            }

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
}

