/*
#ifndef XOR_H
#define XOR_H

//Characteristic for the Neuron Network

#define NUMINPUTS 784
#define NUMHIDNEURONS 1000
#define NUMOUTPUTS 10

//static const int epoch = 10001;

const double lr = 0.1f; //Learning rate 

//Getter
const int numInputs = NUMINPUTS;
const int numHidNeurons = NUMHIDNEURONS;
const int numOutputs = NUMOUTPUTS;

//Hidden Layer Value
double hidLay[NUMHIDNEURONS];
//Output Layer Value
double outputLay[NUMOUTPUTS];

//Hidden Layer Bias for each Neurons
double hidLayBias[NUMHIDNEURONS];
//Output layer Bias for each Neurons
double outputLayBias[NUMOUTPUTS];
*/

/*
   All the weights from : InputLayer to HiddenLayer 
   Here For 2 Hidden: 
   {Input 1 -> Hidden 1 , Input 1 -> Hidden 2}
   {Input 2 -> Hidden 1 , Input 2 -> Hidden 2}
 */

//double hidWeights[NUMINPUTS][NUMHIDNEURONS];

/*
   All the weights from : HiddenLayer to OutputLayer 
   Here For 2 Hidden: 
   {Hidden 1 -> Output 1}
   {Hidden 2 -> Output 1}
 */
/*
double outputWeights[NUMHIDNEURONS][NUMOUTPUTS];

//Training Set

#define SIZETRAINING 4

const int sizeTraining = SIZETRAINING;

const int training[SIZETRAINING][NUMINPUTS] = 
{	
    {0,0},
    {0,1},
    {1,0},
    {1,1}
};

int target[SIZETRAINING][NUMINPUTS] = 
{
    {0},
    {1},
    {1},
    {0}
};

#endif
*/
