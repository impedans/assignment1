#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{	
    // R Peak detection initialization
    QRS_params qsr_params;
    qsr_params.numPeaks = 0;
    qsr_params.PEAKS = malloc(sizeof(double)); // Will contain an unknown amount of elements
    qsr_params.numRPeaks = 0;
    qsr_params.RPEAKS = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements
    qsr_params.numROKPeaks = 0;
    qsr_params.ROKPEAKS = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements
    qsr_params.numRecentRR = 0;
    qsr_params.RecentRR = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements
    qsr_params.numRecentRROK = 0;
    qsr_params.RecentRROK = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements

	FILE *file;                  // Pointer to a file object
	file = openfile("x_mwi.txt");

    //Variable initialization
    double *output = (double*) calloc(3, sizeof(double)); //Inilialize first outputs as zero
    double *input  = (double*) malloc(32 * sizeof(double));
    int num_inputs  = 0;
    int num_outputs = 3;    //Minimum outputs for low pass filter

    while(!feof(file)){
        //Checks for number of datapoints to be sufficient for the lowpass calculations:
        
        /*if(num_inputs > 12){
            //Shift array and remove oldest value
            for(int i=0; i < num_outputs; i++){
                output[i] = output[i+1];
            }

            //Calling lowpass filter
            //lowPassFilter(input, output, num_inputs-1);
            
            //Checks for number of datapoints to be sufficient for the highpass calculations(and thus also the rest)
            if(num_inputs == 32){
                //Shift array, remove oldest value and load newest value
                for (int i = 0; i <= 32; i++){
                    input[i] = input[i+1];
                }
                input[num_inputs] = getNextData(file);

                //Calling filters:
                //highPassFilter(input, output, num_outputs-1);
                //derivativeFilter(input, output, num_outputs-1);
                //squareFilter(output, num_outputs-1);
                //movingWindowIntegration(input, output, num_outputs-1);
            } else{
                //Gets mores inputs if not enough
                input[num_inputs] = getNextData(file);
                num_inputs++;
            }


        } else{
            //Gets more inputs if not enough
            input[num_inputs] = getNextData(file);
            num_inputs++;
        }*/
        
       // Peak detection
       if (num_inputs == 32){
            for(int i=0; i < num_outputs; i++){
                output[i] = output[i+1];
            }
            output[num_inputs] = getNextData(file);
            num_inputs++;
           peakDetection(&qsr_params, output); // Perform Peak Detection
       } else {
            output[num_inputs] = getNextData(file);
            num_inputs++;
       }
        sleep(1);

    }
    

	return 0;
}
