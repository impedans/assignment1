#include "sensor.h"
#include "filters.h"
//#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{	
    //QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");

    //Variable initialization
    double *output = (double*) calloc(3*sizeof(double)); //Inilialize first outputs as zero
    double *input  = (double*) malloc(sizeof(double));
    int num_inputs  = 1;
    int num_outputs = 3;    //Start with the three previously initialized outputs

    while(1){
        //Checks for number of datapoints to be sufficient for the lowpass calculations:
        if(num_inputs >= 12){
            lowPassFilter(input, output, num_outputs);
            
            //Checks for number of datapoints to be sufficient for the highpass calculations(and thus also the rest)
            if(num_inputs >= 32){
                //Shift array, remove oldest value and load newest value
                for (int i = 0; i < 32; i++){
                    input[i] = input[i+1];
                }
                input[31] = getNextData(file);

                highPassFilter(input, output, num_outputs);
                derivativeFilter(input, output, num_outputs);
                squareFilter(input, output);
                movingWindowIntegration(input, output, num_outputs);
            } else{
                //Gets mores inputs if not enough
                num_inputs++;
                input = (double*) realloc(input, num_inputs*sizeof(double));
                input[num_inputs] = getNextData(file);
            }

            num_outputs++;
            output = (double*) realloc(output, num_outputs*sizeof(double));
        } else{
            //Gets more inputs if not enough
            num_inputs++;
            input = (double*) realloc(input, num_inputs*sizeof(double));
            input[num_inputs] = getNextData(file);
        }
    }
    
    //peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
