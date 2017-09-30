#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

// This function compares the last three datapoints in the filtered data and determines if the middle data point is a peak
void peakDetection(QRS_params *params, double filterOutput[])
{
    //for (int i = 1; i < 31; i++){
        //if ((filterOutput[i] > filterOutput[i+1]) && (filterOutput[i] > filterOutput[i-1])){
        // Check if a peak is present at index 30
        if ((filterOutput[30] > filterOutput[31]) && (filterOutput[30] > filterOutput[29])){
            //printf("COMPARING: %lf, %lf, %lf\n", filterOutput[29], filterOutput[30], filterOutput[31]);
            params->PEAKS[params->numPeaks] = filterOutput[30]; // Add the peak to the PEAKS array
            params->numPeaks++; // Increment amount of peaks
            params->PEAKS = realloc(params->PEAKS, (params->numPeaks+1)*sizeof(double)); // Increase size of dynamic array
            //printf("PEAK: %lf, total: %d\n", filterOutput[30], params->numPeaks);
            

            // Check if the peak is above the threshold
            if (filterOutput[30] > params->THRESHOLD1){
                if ((RR > RR_LOW) && (RR < RR_HIGH)){
                    // Store peak as Rpeak
                    PEAK AS RPEAK

                    // The peak is above the threshold, so calculate the RR and update parameters
                    params->SPKF = 0.125*filterOutput[30] + 0.875*params->SPKF;

                    // Shift the RPEAKS and ROKPEAKS arrays to make ready for a new value
                    for (int i = 0; i < 7; i++){ // Make space for the newest element
                        params->RPEAKS[i] = params->RPEAKS[i+1];
                        params->ROKPEAKS[i] = params->ROKPEAKS[i+1];
                    }
                    // Add the R peak to the relevant arrays and increment vars
                    params->RPEAKS[params->numRPeaks] = params->RR;
                    params->ROKPEAKS[params->numROKPeaks] = params->RR;
                    if (params->numRPeaks < 7){
                        params->numRPeaks++;
                    }
                    if (params->numROKPeaks < 7){
                        params->numROKPeaks++;
                    }

                    // Calculate RR_AVERAGE1 and RR_AVERAGE2
                    double temp = 0;
                    for (int i = 0; i < params->numROKPeaks; i++){
                        temp += params->ROKPEAKS[i];
                    }
                    params->RR_AVERAGE2 = temp/params->numROKPeaks;
                    temp = 0;
                    for (int i = 0; i < params->numRPeaks; i++){
                        temp += params->RPEAKS[i];
                    }
                    params->RR_AVERAGE1 = temp/params->numRPeaks;

                    // Calculate other parameters
                    params->RR_LOW = 0.92*params->RR_AVERAGE2;
                    params->RR_HIGH = 1.16*params->RR_AVERAGE2;
                    params->RR_MISS = 1.66*params->RR_AVERAGE2;
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;
                } else if (RR > RR_MISS){
                    // Search through all peaks and find the first peak above THRESHOLD2
                    double peak2;
                    for (int i = 0; i < params->numPeaks; i++){
                       if (params->PEAKS[i] > params->THRESHOLD2){
                        peak2 = params->PEAKS[i];
                        break;
                       } 
                    }
                    // Store peak2 as RPEAK
                    PEAK2 AS RPEAK

                    // Calculate SPKF again
                    params->SPKF = 0.25*peak2 + 0.75*params->SPKF;

                    // Store RR in recentRR

                    // Update RR_AVERAGE 1
                    double temp = 0;
                    for (int i = 0; i < params->numRPeaks; i++){
                        temp += params->RPEAKS[i];
                    }
                    params->RR_AVERAGE1 = temp/params->numRPeaks;

                    // Calculate RR_LOW, RR_HIGH and RR_MISS and thresholds
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;

                }

            } else {
                // The peak is below the threshold, so it's noise, therefore modify the following parameters
                params->NPKF = 0.125*filterOutput[30] + 0.875*params->NPKF;
                params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                params->THRESHOLD2 = 0.5*params->THRESHOLD1;
            }


        }
    //}
}
