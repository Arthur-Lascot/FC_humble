#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <err.h>

#include "backprop.h"
#include "forward.h"
#include "network_tools.h"


//Characteristic for the Neuron Network

#define NUMINPUTS 2
#define NUMHIDNEURONS 4
#define NUMOUTPUTS 1

static const int epoch = 10001;

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

/*
   All the weights from : InputLayer to HiddenLayer 
   Here For 2 Hidden: 
   {Input 1 -> Hidden 1 , Input 1 -> Hidden 2}
   {Input 2 -> Hidden 1 , Input 2 -> Hidden 2}
 */
double hidWeights[NUMINPUTS][NUMHIDNEURONS];

/*
   All the weights from : HiddenLayer to OutputLayer 
   Here For 2 Hidden: 
   {Hidden 1 -> Output 1}
   {Hidden 2 -> Output 1}
 */
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

int research_input(char* input1, char* input2)
{
    for (int i = 0; i < sizeTraining; i++)
    {
        if (training[i][0] == *input1-'0')
        {
            if (training[i][1] == *input2-'0')
            {
                return i;
            }
        }
    }
    return -1;
}

//Generate a random number between 0.25f and 0.75f;
double random_double()
{
    double res = rand() % 101;

    if (res == 0)
        return 0;
    return (res/100);
}

//Generate a random number between 0 and 3 (4);
int random_four()
{
    double res = rand() % 4;
    return res;
}

//Mix the test
void mix(int training[],size_t size)
{
    for (size_t n = 0; n < size ; n++)
    {
        int move = random_four();
        move = (n+move)%size;
        //Swap training
        int tmp = training[n];
        training[n] = training[move];
        training[move] = tmp;
    }
}

void init_network()
{
    //Fill all the weights from Input to Hidden with random value 
    for (int i = 0; i < numInputs ; i++)
    {
        for (int j = 0; j < numHidNeurons ; j++)
        {
            hidWeights[i][j] = random_double();
        }
    }

    for (int i = 0; i < numHidNeurons ; i++)
    {
        //Fill the Bias of the Hidden Layer with random value
        hidLayBias[i] = random_double();
        //Fill all the weights from Hidden to Output with random value
        for (int j=0; j < numOutputs; j++)
        {
            outputWeights[i][j] = random_double();
        }
    }

    //Fill the Bias of the Output Layer with random value
    for (int i = 0; i <numOutputs; i++)
    {
        outputLayBias[i] = random_double();
    }
}

void print_value_net()
{
    printf("\n========== Values =========\n\n");

    printf(" => Weights :\n\n");
    for (int i = 0; i < numInputs ; i++)
    {
        for (int j = 0; j < numHidNeurons ; j++)
        {
            printf("Hidden Weights %i-->%i = %f\n",i,j,hidWeights[i][j]);
        }
    }

    printf("\n");
    for (int i = 0; i < numHidNeurons ; i++)
    {
        for (int j=0; j < numOutputs; j++)
        {
            printf("Output Weights %i-->%i = %f\n",i,j,outputWeights[i][j]);
        }
    }

    printf("\n");
    printf(" => Bias :\n\n");
    for (int i = 0; i < numHidNeurons; i++)
    {
        printf("Hidden Bias [%i] = %f\n",i,hidLayBias[i]);
    }
    printf("\n");
    for (int i = 0; i <numOutputs; i++)
    {
        printf("Output Bias [%i] = %f\n",i,outputLayBias[i]);
    }

    printf("===========================\n\n");

}

//Return 1 if the inputs are valid for a xor function
int testing_inputs(char *input1, char *input2)
{
        if (lenstr(input1) != 1 || lenstr(input2) != 1)
        {
            printf("input_1 = %s\n",input1);
            printf("input_2 = %s\n",input2);
            return 0;
            //errx(1,"Usage: path [0-1][0-1]");
        }

        if (*input1 != '0' && *input1 != '1')
        {
            printf("input_1 = %s\n",input1);
            return 0;
            //errx(1,"Usage: path [0-1][0-1]");
        }
        if (*input2 != '0' && *input2 != '1')
        {
            printf("input_2 = %s\n",input2);
            return 0;
            //errx(1,"Usage: path [0-1][0-1]");
        }
        return 1;
}


//Write a file with values of the neural network
void write(FILE *path)
{
    for (int i = 0; i < numInputs ; i++)
    {
        for (int j = 0; j < numHidNeurons ; j++)
        {
            fprintf(path,"%lf\n",hidWeights[i][j]);
        }
    }

    for (int i = 0; i < numHidNeurons ; i++)
    {
        for (int j=0; j < numOutputs; j++)
        {
            fprintf(path,"%lf\n",outputWeights[i][j]);
        }
    }

    for (int i = 0; i < numHidNeurons; i++)
    {
        fprintf(path,"%lf\n",hidLayBias[i]);
    }
    for (int i = 0; i <numOutputs; i++)
    {
        fprintf(path,"%lf\n",outputLayBias[i]);
    }
    fclose(path);
}

//Write a file with values of the neural network
void read(FILE *path)
{
    for (int i = 0; i < numInputs ; i++)
    {
        for (int j = 0; j < numHidNeurons ; j++)
        {
            fscanf(path,"%lf\n",&hidWeights[i][j]);
        }
    }

    for (int i = 0; i < numHidNeurons ; i++)
    {
        for (int j=0; j < numOutputs; j++)
        {
            fscanf(path,"%lf\n",&outputWeights[i][j]);
        }
    }

    for (int i = 0; i < numHidNeurons; i++)
    {
        fscanf(path,"%lf\n",&hidLayBias[i]);
    }
    for (int i = 0; i <numOutputs; i++)
    {
        fscanf(path,"%lf\n",&outputLayBias[i]);
    }
    fclose(path);
}



int main(int argc,char** argv)
{
    //====> Initialization <====//
    if (argc != 2 && argc != 4)
        errx(1,"Usage: path [0-1][0-1]");

    char *path = argv[1]; 

    FILE *filenet = fopen(path,"r");

    int reading = 1; //Reading or Writing a file
    int testing = (argc == 4); //Testing with value
    
    char *input_1 = 0;
    char *input_2 = 0;
    //Checks good values for testing
    if (testing)
    {
        input_1 = argv[2];
        input_2 = argv[3];
        
        if (!testing_inputs(input_1,input_2))
            errx(1,"Usage: path [0-1][0-1]");
    }

    if (filenet == NULL)
    {
        filenet = fopen(path,"w");
        reading = 0;
        if (filenet == NULL)
            errx(1,"Error : Could not write the network file");
    }

    //=========================//
    /*                         */
    //====> Training Part <====//
    if (!reading)
    {
        time_t t;
        int n = 0;

        //Initializes random number generator
        srand((unsigned) time(&t));    

        init_network();
        print_value_net();

        int trainingOrder[] = {0, 1, 2, 3};

        while (n < epoch)
        { 
            if (n%1000 == 0)
                printf("\n===============> EPOCH N°%i <================\n",n);

            mix(trainingOrder,sizeTraining);

            /* Print the training order:
               if (n%1000 == 0)
               {
               printf("Training Order : {");
               for (int h = 0 ; h < sizeTraining;h++)
               {
               printf("%i",trainingOrder[h]);
               }
               printf("}\n\n");
               }
             */
            for (int x=0; x< 4; x++) 
            {    
                int i = trainingOrder[x];

                if (n%1000 == 0)
                {
                    //Print the training set
                    //printf("   Set training N°%i \n",x);
                    printf(" [%i] XOR [%i] => ",training[i][0],training[i][1]);
                }

                //Forward
                forward(i,n);

                //BackProp
                backprop(i,n); 
            }
            n++;
        }
    }
    //========================//
    /*                        */
    //====> Fetching Part <===//
    if (reading)
    {
        read(filenet);
        printf("\nReading .../\n\n");
    }
    //========================//
    /*                        */
    //====> Testing Part <====//
    if (testing)
    {
        int index = research_input(input_1,input_2);
        printf("########## RESULT ##########\n|\n");
        printf("|  [%d] XOR [%d] => ",*input_1-'0',*input_2-'0');
        forward(index,0);
        printf("|\n");
        printf("############################\n");

    }



    //========================//

    print_value_net();
    if (!reading)
    {
        write(filenet);
        printf("\nWriting ..../\n");
    }
    printf("Done\n");

    return 1;
}

