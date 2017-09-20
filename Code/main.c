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

    int *initialDataPoints = (int*) malloc(3*sizeof(int));
    initialDataPoints[0] = getNextData(file);          // Read Data from Sensor
    numDataPoints++;
    initialDataPoints[1] = getNextData(file);          // Read Data from Sensor
    numDataPoints++;
    initialDataPoints[2] = getNextData(file);          // Read Data from Sensor
    numDataPoints++;

    lowPassFilter();            // Filter Data
    //peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}