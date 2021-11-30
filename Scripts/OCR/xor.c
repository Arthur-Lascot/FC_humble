#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <err.h>

//#include <sys/types.h>
//#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>


#include "xor.h"
#include "backprop.h"
#include "forward.h"
#include "network_tools.h"
#include "reader.h"

//Characteristic for the Neuron Network

#define NUMINPUTS 784
#define NUMHIDNEURONS 98
#define NUMOUTPUTS 9

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
    double res = rand() % 201;

    if (res == 0)
        return 0;
    return ((res/100)-1);
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
void write_net(FILE *path)
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
void read_net(FILE *path)
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

int xr(int reading,FILE* filenet,double img[NUMINPUTS])
{

    load_data();

    //First tenth train:
    // 5-0-4-1-9-2-1-3-1-4 

    /*int numz = 0;
      for (int i = 0; i<TEST_DATA;i++)
      {
      if (test_label[i] == 0)
      numz++;
      }
      printf("Num Zero : %i",numz);
     */
    double* res = malloc(sizeof(double));


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
        //print_value_net();

        while (n < 2.5*60000)
        { 
            if (train_label[n%TRAIN_DATA] != 0)
            {
                if (n%1000 == 0)
                    printf("\n==============> EPOCH N°%i <===============\n",n);

                //Forward
                int result = forward(res,n,1,0,NULL);

                //BackProp
                backprop(result,n);
            }
            else 
            {
                if (n%1000 == 0)
                    printf("SKIPPED !");
            }
            n+=1;
        }
    }

    //========================//
    /*                        */
    //====> Fetching Part <===//
    if (reading)
    {
        double rate = 0.0f;

        FILE *defaul;
        if (filenet == NULL)
        {
            printf("Default File\n");
            defaul = fopen("../OCR/test","r");
            if (defaul == NULL)
                errx(1,"Could not open the default file");
            read_net(defaul);
            for (int j = 0; j<NUMOUTPUTS;j++)
            {
                printf("OutPutLayBias[%i] = %f  ",j,outputLayBias[j]);
            }
        }
        else
        {
            read_net(filenet);
        }
        
        printf("\nReading .../\n\n");

        if (img != NULL)
        {
            /*
            for (int i=0; i<784; i++) 
            {
                if (image[i] >= 0.5f)
                    printf("1 ");
                else 
                    printf("  ");
                if ((i+1) % 28 == 0) putchar('\n');
            }
            */

            int result = forward(res,1,0,0,img);
            printf("RESULT : %i => %f\n",result,*res);
            free(res);
            return result;
        }
        else 
        {
            printf("Here");
            for (int j = 0 ; j < TEST_DATA ; j++)
            {
                if (test_label[j] != 0)
                {
                    if (j%1000 == 0)
                        printf("\n============> EPOCH N°%i <=============\n",j);
  
                    int result = forward(res,j,0,1,NULL);
                    if (result == test_label[j])
                        rate++;
                }
                else 
                {
                    if (j%1000 == 0)
                        printf("SKIPPED !");
                }
            }
            rate = (rate/TEST_DATAZ)*100;
            printf("\n===============> RESULT <===============\n");
            printf("%f/100 SUCESS RATE ",rate);
            printf("\n===============> RESULT <===============\n");
        }

    }
    //print_value_net();
    if (!reading)
    {
        write_net(filenet);
        printf("\nWriting ..../\n");
    }

    printf("Done\n");
    free(res);
    return 1;
}











