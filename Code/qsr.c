#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

// This function compares the last three datapoints in the filtered data and determines if the middle data point is a peak
void peakDetection(QRS_params *params, int *filterOutput)
{
    //printf("INPUTS 1 2 0 : %d, %d, %d\n", filterOutput[1], filterOutput[2], filterOutput[0]);
        // Check if a peak is present at index 1
        if ((filterOutput[1] > filterOutput[2]) && (filterOutput[1] > filterOutput[0])){
            //printf("PEAK PRESENT\n");
            params->PEAKS[params->numPeaks] = filterOutput[1]; // Add the peak to the PEAKS array
            params->numPeaks++; // Increment amount of peaks
            params->PEAKS = realloc(params->PEAKS, (params->numPeaks+1)*sizeof(int)); // Increase size of dynamic array

            // Check if the peak is above the threshold
            if (filterOutput[1] > params->THRESHOLD1){
                //printf("ABOVE THRESHOLD\n");

                //printf("samples: %d\n", params->samplesSinceLastRpeak);
                double RR = params->samplesSinceLastRpeak/250;
                
                params->samplesSinceLastRpeak = 0;
                //printf("RR: %lf\n", RR);

                //printf("checking: %lf > %lf and %lf < %lf\n", RR, params->RR_LOW, RR, params->RR_HIGH);
                if ((RR > params->RR_LOW) && (RR < params->RR_HIGH)){
                    // Store peak as Rpeak
                    printf("ADDING RPEAK: %d\n", filterOutput[1]);
                    params->RPEAKS[params->numRPeaks] = filterOutput[1];
                    params->numRPeaks++;

                    // The peak is above the threshold, so calculate the RR and update parameters
                    params->SPKF = 0.125*filterOutput[1] + 0.875*params->SPKF;

                    // Store RR element in RecentRR and RecentRROK
                    if(params->numRecentRR < 7){
                        params->RecentRR[params->numRecentRR] = RR;
                        params->numRecentRR++;
                    } else {
                       for (int i = 0; i < params->numRecentRR; i++){
                            params->RecentRR[params->numRecentRR] = params->RecentRR[params->numRecentRR+1];
                       } 
                       params->RecentRR[params->numRecentRR] = RR;
                    }
                    if(params->numRecentRROK < 7){
                        params->RecentRROK[params->numRecentRROK] = RR;
                        params->numRecentRROK++;
                    } else {
                       for (int i = 0; i < params->numRecentRROK; i++){
                            params->RecentRROK[params->numRecentRROK] = params->RecentRROK[params->numRecentRROK+1];
                       } 
                       params->RecentRROK[params->numRecentRROK] = RR;
                    }

                    // Calculate the RR averages
                    int temp = 0;
                    for (int i = 0; i < params->numRecentRR; i++){
                        temp += params->RecentRR[i];
                    } 
                    params->RR_AVERAGE2 = temp/params->numRecentRR;
                    temp = 0;
                    for (int i = 0; i < params->numRecentRROK; i++){
                        temp += params->RecentRROK[i];
                    } 
                    params->RR_AVERAGE1 = temp/params->numRecentRROK;

                    // Calculate other parameters
                    params->RR_LOW = 0.92*params->RR_AVERAGE2;
                    params->RR_HIGH = 1.16*params->RR_AVERAGE2;
                    params->RR_MISS = 1.66*params->RR_AVERAGE2;
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;

                } else if (RR > params->RR_MISS){
                    double peak2;
                    // Search through all peaks and find the first peak above THRESHOLD2
                    for (int i = params->numPeaks-1; i >= 0; i--){
                       if (params->PEAKS[i] > params->THRESHOLD2){
                        peak2 = params->PEAKS[i];
                        break;
                       } 
                    }
                    printf("MISS, adding %lf via searchback\n", peak2);
                    // Store peak2 as RPEAK
                    params->RPEAKS[params->numRPeaks] = peak2;
                    params->numRPeaks++;

                    // Calculate SPKF again
                    params->SPKF = 0.25*peak2 + 0.75*params->SPKF;

                    // Store RR in recentRR
                    if(params->numRecentRR < 7){
                        params->RecentRR[params->numRecentRR] = RR;
                        params->numRecentRR++;
                    } else {
                       for (int i = 0; i < params->numRecentRR; i++){
                            params->RecentRR[params->numRecentRR] = params->RecentRR[params->numRecentRR+1];
                       } 
                       params->RecentRR[params->numRecentRR] = RR;
                    }

                    // Update RR_AVERAGE 1
                    int temp = 0;
                    for (int i = 0; i < params->numRPeaks; i++){
                        temp += params->RPEAKS[i];
                    }
                    params->RR_AVERAGE1 = temp/params->numRPeaks;

                    // Calculate RR_LOW, RR_HIGH and RR_MISS and thresholds
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;

                } else {
                    
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;
                }

            } 
            
        }
}
