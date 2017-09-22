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
    double *output = (double*) malloc(sizeof(double)) 

    while(1){
        GET SOMETHING

        //Checks for number of datapoints to be sufficient for the lowpass calculations:
        if(PLACEHOLDER > LIMIT){
            DOSTUFF
        }

        //Checks for number of datapoints to be sufficient for the highpass calculations(and thus also the rest)
        if(PLACEHOLDER > LIMIT){
            DO EVEN MORE STUFF
        }

        INCREMENT SOMETHING
    }
    
    //peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
