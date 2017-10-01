#include "sensor.h"
#include "filters.h"
//#include "qsr.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{	
    //QRS_params qsr_params;       // Instance of the made avaiable through: #include "qsr.h"
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
            
            sleep(1);
        }else{
            //Gets more inputs if not enough
            num_inputs++;
            input[num_inputs-1] = getNextData(file);
        }    

        //Make the final input visible for the low pass filter
        output_temp1[num_inputs-1] = output[num_inputs-1];

        //Filters are applied:
        lowPassFilter(input, output_temp1, num_inputs-1);
        highPassFilter(output_temp1, output_temp2, num_inputs-1);
        derivativeFilter(output_temp2, output_temp3, num_inputs-1);
        squareFilter(output_temp3, num_inputs-1);
        movingWindowIntegration(output_temp3, output, num_inputs-1);

        //Debugging
        //Final action:
        printf("\nItteration: %d. Outputs: %d, %d, %d To inputs: %d, %d, %d\n",num_inputs, output[num_inputs-1], output[num_inputs-2], output[num_inputs-3], input[num_inputs-1], input[num_inputs-2], input[num_inputs-3]);


    }
    
    //peakDetection(&qsr_params); // Perform Peak Detection

	return 0;
}
