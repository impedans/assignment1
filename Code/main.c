#include "sensor.h"
#include "filters.h"
//#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

int numDataPoints = 0; // Used to keep track of datapoint array size for use with malloc

int main()
{	
    //QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
	FILE *file;                  // Pointer to a file object
	file = openfile("ECG.txt");

    // Define the array holding the sampled data and the filtered data, respectively.
    // 32 is the max size we're gonna be working with
    int *sampledDatapoints = (int*) malloc(42*sizeof(int));
    int *filteredDatapoints = (int*) malloc(32*sizeof(int));

    // Sample 12 data points 
    numDataPoints = 12;
    for (int i = 0; i < numDataPoints; i++){
        sampledDatapoints[i] = getNextData(file);
    }

    // pass the last two data points to the filter array
    filteredDatapoints[0] = sampledDatapoints[10];
    filteredDatapoints[1] = sampledDatapoints[11];

    int filterIndex = 2; // Start index for filtering
    int temp = 1;
    while(1){
        if (numDataPoints > 42){ // Only increase the array size if less than size 32
            // Shift array once to the left and get new sample
            for (int i = 0; i < 31; i++){
                sampledDatapoints[i] = sampledDatapoints[i+1];
            }
            sampledDatapoints[31] = getNextData(file);

            // Do all the filters
            lowPassFilter(sampledDatapoints, filteredDatapoints, filterIndex);
            highPassFilter(sampledDatapoints, filteredDatapoints, filterIndex);
            derivativeFilter(sampledDatapoints, filteredDatapoints, filterIndex);
            squareFilter(filteredDatapoints, filterIndex);
            movingWindowIntegration(sampledDatapoints, filteredDatapoints, filterIndex);

        } else {
            // Sample the data point
            sampledDatapoints[numDataPoints] = getNextData(file);
            numDataPoints++;

            // Start lowpass-filtration at index 2 and increase with each iteration
            lowPassFilter(sampledDatapoints, filteredDatapoints, filterIndex);
            filterIndex++;
        }

        // Print the filtered values
        printf("%d,", filteredDatapoints[filterIndex]);
        if (temp > 200){
            break;
        }
        temp++;
    }

    

    //peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
