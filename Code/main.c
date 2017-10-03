#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{	
    QRS_params qrs_params;
    qrs_params.numPeaks = 0;
    qrs_params.PEAKS = malloc(sizeof(int)); // Will contain an unknown amount of elements
    //qsr_params.PEAKS = malloc(sizeof(double)); // Will contain an unknown amount of elements
    qrs_params.numRPeaks = 0;
    qrs_params.RPEAKS = malloc(sizeof(int)); // Will contain an unknown amount of RPeaks
    qrs_params.numRecentRR = 0;
    qrs_params.RecentRR = calloc(8, 8*sizeof(int)); // Will only contain at most 8 elements
    //qsr_params.RecentRR = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements
    qrs_params.numRecentRROK = 0;
    qrs_params.RecentRROK = calloc(8, 8*sizeof(int)); // Will only contain at most 8 elements
    //qsr_params.RecentRROK = calloc(8, 8*sizeof(double)); // Will only contain at most 8 elements

    qrs_params.samplesSinceLastRpeak = 0;
    qrs_params.samplesSinceLastRpeakTemp = 0;
    //qsr_params.THRESHOLD1 = 0;
    //qsr_params.THRESHOLD2 = 0;
    //qsr_params.RR_LOW = 0;
    //qsr_params.RR_HIGH = 0;
    //qsr_params.RR_MISS = 0;
    
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");

    //Variable initialization
    int *output_temp1 = (int*) calloc(33 , sizeof(int)); //Inilialize first outputs as zero
    int *output_temp2 = (int*) calloc(33 , sizeof(int)); //Inilialize first outputs as zero
    int *output_temp3 = (int*) calloc(33 , sizeof(int)); //Inilialize first outputs as zero
    int *output = (int*) calloc(33 , sizeof(int));
    int *input  = (int*) malloc(33 * sizeof(int));
    int num_inputs  = 0;

    while(!feof(file)){
        //If the arrays have reached maximum size, they begin to rotate
        if(num_inputs == 33){
            //Shift array, remove oldest value and load newest value
            for (int i = 0; i < num_inputs-1; i++){
                input[i] = input[i+1];
                output_temp1[i] = output_temp1[i+1];
                output_temp2[i] = output_temp2[i+1];
                output_temp3[i] = output_temp3[i+1];
                output[i] = output[i+1];
            }
            input[num_inputs-1] = getNextData(file);
            
            //sleep(1);
        }else{
            //Gets more inputs if not enough
            num_inputs++;
            input[num_inputs-1] = getNextData(file);
        }    

        qrs_params.samplesSinceLastRpeak++;
        qrs_params.samplesSinceLastRpeakTemp++;

        //Make the final input visible for the low pass filter
        output_temp1[num_inputs-1] = output[num_inputs-1];

        //Filters are applied:
        lowPassFilter(input, output_temp1, num_inputs-1);
        highPassFilter(output_temp1, output_temp2, num_inputs-1);
        derivativeFilter(output_temp2, output_temp3, num_inputs-1);
        squareFilter(output_temp3, num_inputs-1);
        movingWindowIntegration(output_temp3, output, num_inputs-1);
        //printf("%d, %d\n", qsr_params.samplesSinceLastRpeakTemp-1, output[num_inputs-1]);
        peakDetection(&qrs_params, output, num_inputs);

        //Debugging
        //Final action:
        //printf("\nItteration: %d. Outputs: %d, %d, %d To inputs: %d, %d, %d\n",num_inputs, output[num_inputs-1], output[num_inputs-2], output[num_inputs-3], input[num_inputs-1], input[num_inputs-2], input[num_inputs-3]);
        //
        // Print all R-peaks


    }
    
    // Output the Rpeaks to console
    for (int i = 0; i < qrs_params.numRPeaks; i++){
        printf("%d\n", qrs_params.RPEAKS[i]);
    }

    //for (int i = 0; i < 33; i++){
        //printf("output[i]: %d\n", output[i]);
    //}

	return 0;
}
