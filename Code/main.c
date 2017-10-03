#include "sensor.h"
#include "filters.h"
#include "qsr.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{	
    //Variable initialization for QRS calculations
    QRS_params qrs_params;
    qrs_params.numPeaks = 0;
    qrs_params.PEAKS = malloc(sizeof(int)); // Will contain an unknown amount of elements
    qrs_params.numRPeaks = 0;
    qrs_params.RPEAKS = malloc(sizeof(int)); // Will contain an unknown amount of RPeaks
    qrs_params.numRecentRR = 0;
    qrs_params.RecentRR = calloc(8, 8*sizeof(int)); // Will only contain at most 8 elements
    qrs_params.numRecentRROK = 0;
    qrs_params.RecentRROK = calloc(8, 8*sizeof(int)); // Will only contain at most 8 elements

    qrs_params.samplesSinceLastRpeak = 0;
    qrs_params.samplesSinceLastRpeakTemp = 0;
    
    //Pointer to a file object
	FILE *file;
	file = openfile("ECG.txt");

    //Variable initialization for filter calculations
    int *output_temp1 = (int*) malloc(33 * sizeof(int)); //Inilialize first outputs as zero
    int *output_temp2 = (int*) malloc(33 * sizeof(int)); //Inilialize first outputs as zero
    int *output_temp3 = (int*) malloc(33 * sizeof(int)); //Inilialize first outputs as zero
    unsigned int *output = (int*) malloc(33 * sizeof(int));
    int *input  = (int*) malloc(33 * sizeof(int));
    short index   = 0;

    //Runs until 'end of file'
    while(!feof(file)){
        //If the arrays have reached maximum size, they begin to rotate
        if(index == 33){
            //Rotate array, remove oldest value and load newest value
            for (int i = 0; i < 32; i++){
                output_temp1[i] = output_temp1[i+1];
                output_temp2[i] = output_temp2[i+1];
                output_temp3[i] = output_temp3[i+1];
                output[i] = output[i+1];
                input[i] = input[i+1];
            }

            input[index-1] = getNextData(file);
        }else{
            //Gets more inputs if not enough
            index++;
            input[index-1] = getNextData(file);
        }    

        qrs_params.samplesSinceLastRpeak++;
        qrs_params.samplesSinceLastRpeakTemp++;

        //Make the final input visible for the low pass filter
        output_temp1[index-1] = output[index-1];

        //Filters are applied:
        lowPassFilter(input, output_temp1, index-1);
        highPassFilter(output_temp1, output_temp2, index-1);
        derivativeFilter(output_temp2, output_temp3, index-1);
        squareFilter(output_temp3, index-1);
        movingWindowIntegration(output_temp3, output, index-1);
        peakDetection(&qrs_params, output, index-1);
    }
    
    // Output the Rpeaks to console
    for (int i = 0; i < qrs_params.numRPeaks; i++){
        printf("%d\n", qrs_params.RPEAKS[i]);
    }

	return 0;
}

